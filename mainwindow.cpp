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
    ui->solutionTable->setRowCount(0);
    for (int j = 0; j < probs.size(); j++) {
        ui->solutionTable->insertRow(j);
    }
    for (int j = 0; j < probs.size(); j++) {

        QTableWidgetItem *item = new QTableWidgetItem(probs.at(j).first);
        ui->solutionTable->setItem(j, 0,item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(probs.at(j).second));
        ui->solutionTable->setItem(j, 1, item2);
    }
}


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
}

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
}

void MainWindow::on_startButton_clicked()
{
    IA.start(filePath);
    ProbabilitiesCalculator prob;
    prob.calculate(IA.getData(), IA.getTotalPixels());
    probs = prob.getProbabilities();
    startTable();
    HA.setProbabilities(probs);
    HA.run();
    QVector< QPair<QString, QString> > solution = HA.getSolution();
    updateTable(solution);
    HA.setData(this->lenghtData());
    ui->LBox->setText(QString::number(HA.getAverageLength()));
    ui->HBox->setText(QString::number(HA.getEntropy()));
    ui->nBox->setText(QString::number(HA.getPerformance()));
}


void MainWindow::on_aboutButton_clicked()
{
    aboutWindow.setWindowTitle("About");
    aboutWindow.show();
}
