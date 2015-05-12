#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("Image (*.png)");
    int result = dialog.exec();
    if (result)
        filePath = dialog.selectedFiles().first();
    else
        filePath = "";
    fileName = getFileName();
    displayText();
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

/*
void MainWindow::updateTable(QVector< QPair<QString, QString> > solution)
{

    for (int j = 0; j < solution.size(); j++) {
        int i = 0;
        bool done = false;
        while (i < probs.size() && !done) {
            if ((probs.at(i).first) == (solution.at(j)).first) {
                QTableWidgetItem *item = new QTableWidgetItem(solution.at(j).second);
                ui->solutionTable->setItem(i,2, item);
                QString code = solution.at(j).second;
                int lenght = code.length();
                QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(lenght));
                ui->solutionTable->setItem(i,3, item2);
                done = true;
            }
            else
                i++;
        }
    }
}*/
/*
QVector< QPair<int, double> > MainWindow::lenghtData()
{
    QVector< QPair<int, double> > data;
    for (int i = 0; i < probs.size(); i++) {
        QTableWidgetItem *proba = ui->solutionTable->item(i, 1);
        QTableWidgetItem *lenght = ui->solutionTable->item(i, 3);
        QString probaText = (*proba).text();
        QString lenghtText = (*lenght).text();
        double p = probaText.toDouble();
        int l = lenghtText.toInt();
        data.append(qMakePair(l, p));
    }
    return data;
}*/

void MainWindow::on_startButton_clicked()
{
    IA.start(filePath);

    this->orderOneSymbols = prob.calculate(IA.getColorCount(), IA.getTotalPixels());

    //probs = prob.getProbabilities(); NO SE NECESITA MAS


    HA.calculateHuffman(orderOneSymbols);

    for (int i = 0; i < orderOneSymbols.size(); i++) {
        qDebug() << orderOneSymbols.at(i).getColors();
        qDebug() << "PROBABILITY" << orderOneSymbols.at(i).getProbability();
        qDebug() << "HUFFCODE" << orderOneSymbols.at(i).getHuffmanCode();
    }
    qDebug() << "antes de cargar los datos ORDEN 1";
    startTable();

    /*for (int i = 0; i < symbCodification.size(); i++) {
        for (int e = 0; e < symbCodification.at(i).first.size(); e++) {
            qDebug() << symbCodification.at(i).first.at(e);
        }
        qDebug() << "CODIGO: " << symbCodification.at(i).second;
    }*/

    //updateTable(solution);
    /*HA.setData(this->lenghtData());
    ui->LBox->setText(QString::number(HA.getAverageLength()));
    ui->HBox->setText(QString::number(HA.getEntropy()));
    ui->nBox->setText(QString::number(HA.getPerformance()));*/
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
    qDebug() << "antes de cargar los datos ORDEN "<<n;
    nExtensionWindow.loadData(orderNSymbols);
    nExtensionWindow.setWindowTitle("N-EXTENSION");

}
