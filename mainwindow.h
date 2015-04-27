#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include "imageanalyzer.h"
#include "probabilitiescalculator.h"
#include "huffmanalgorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectFileButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
    QString getFileName();
    QString fileName;
    void displayText();
    void displayDataText();
    void startTable();
    void updateTable(QVector< QPair<QString, QString> > solution);
    QVector< QPair<int, double> > lenghtData();
    HuffmanAlgorithm HA;
    ImageAnalyzer IA;
    QVector< QPair<QString, double> > probs;
};

#endif // MAINWINDOW_H
