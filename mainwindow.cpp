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
    for (int j = 0; j < symbols.size(); j++) {
        ui->solutionTable->insertColumn(j);
    }
    for (int j = 0; j < symbols.size(); j++) {
        QString symbolString;
        symbolString.append("{");
        for (int i = 0; i < symbols.at(j).getColors().size(); i++) {
            if (i != 0) {
                symbolString.append(", ");
            }
            symbolString.append(symbols.at(j).getColors().at(i));
        }
        symbolString.append("}");

        QTableWidgetItem *item = new QTableWidgetItem(symbolString);
        ui->solutionTable->setItem(0, j,item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(symbols.at(j).getProbability()));
        ui->solutionTable->setItem(1, j, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(symbols.at(j).getHuffmanCode());
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
    ProbabilitiesCalculator prob;
    prob.calculate(IA.getColorCount(), IA.getTotalPixels());


    QString nText = ui->NBox->toPlainText();
    int n = nText.toInt();

    prob.extend(n, symbols);
    //probs = prob.getProbabilities(); NO SE NECESITA MAS

    //startTable();

    HA.calculateHuffman(symbols);

    for (int i = 0; i < symbols.size(); i++) {
        qDebug() << symbols.at(i).getColors();
        qDebug() << "PROBABILITY" << symbols.at(i).getProbability();
        qDebug() << "HUFFCODE" << symbols.at(i).getHuffmanCode();
    }

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
