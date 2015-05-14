#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->compressButton->setDisabled(true);
    ui->extendButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setNameFilter("Image");
    int result = dialog.exec();
    if (result)
        filePath = dialog.selectedFiles().first();
    else
        filePath = "";
    fileName = getFileName();
    this->displayText();
}

QString MainWindow::getFileName()
{
    QChar a = '/'; //if normal OS
    int index = filePath.lastIndexOf(a);
    if (index == -1){ //if Windows
        a = '\\';
        index = filePath.lastIndexOf(a);
    }
    int n = filePath.size()-index-1;
    return filePath.right(n);
}

void MainWindow::displayText()
{
    ui->fileNameBox->setText(fileName);
}

void MainWindow::startTable()
{
    ui->solutionTable->setColumnCount(0);
    for (int j = 0; j < orderOneSymbols.size(); j++) {
        ui->solutionTable->insertColumn(j);
        QString orderOneSymbolstring;
        orderOneSymbolstring.append("{");
        for (int i = 0; i < orderOneSymbols.at(j).getColors().size(); i++) {
            if (i != 0) {
                orderOneSymbolstring.append(", ");
            }
            orderOneSymbolstring.append(orderOneSymbols.at(j).getColors().at(i));
        }
        orderOneSymbolstring.append("}");
        QTableWidgetItem *item = new QTableWidgetItem(orderOneSymbolstring);
        ui->solutionTable->setItem(0, j,item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(orderOneSymbols.at(j).getProbability()));
        ui->solutionTable->setItem(1, j, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(orderOneSymbols.at(j).getHuffmanCode());
        ui->solutionTable->setItem(2, j, item3);
    }
}

void MainWindow::on_startButton_clicked()
{
    IA.start(filePath);
    this->orderOneSymbols.clear();
    this->orderOneSymbols = prob.calculate(IA.getColorCount(), IA.getTotalPixels());
    HA.calculateHuffman(orderOneSymbols);
    this->startTable();
    ui->LBox->setText(QString::number(HA.getAverageLength()));
    ui->HBox->setText(QString::number(HA.getEntropy()));
    ui->nBox->setText(QString::number(HA.getPerformance()));
    ui->compressButton->setDisabled(false);
    ui->extendButton->setDisabled(false);
}

void MainWindow::on_aboutButton_clicked()
{
    aboutWindow.setWindowTitle("About");
    aboutWindow.show();
}

void MainWindow::on_extendButton_clicked()
{
    nExtensionWindow.setWindowTitle("DATA CALCULATION COMPLETE, PLEASE WAIT");
    QString nText = ui->NBox->toPlainText();
    int n = nText.toInt();
    orderNSymbols.clear();
    prob.extend(n, orderNSymbols);
    nExtensionWindow.show();
    nExtensionWindow.loadData(orderNSymbols);
    nExtensionWindow.setWindowTitle("N-EXTENSION");
}

void MainWindow::on_compressButton_clicked()
{
    FileCompressor FC;
    QVector<QString> image = IA.toVector();
    int height = IA.getHeight();
    int width = IA.getWidth();
    FC.compress(orderOneSymbols, image, height, width);
}

void MainWindow::on_decompressButton_clicked()
{
    FileDecompressor FDC;
    FDC.decompress();
}
