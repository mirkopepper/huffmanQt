#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include "imageanalyzer.h"
#include "probabilitiescalculator.h"
#include "huffmanalgorithm.h"
#include "about.h"
#include "symbol.h"
#include "nextension.h"
#include "filecompressor.h"
#include "filedecompressor.h"

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

    void on_aboutButton_clicked();

    void on_extendButton_clicked();

    void on_compressButton_clicked();

    void on_decompressButton_clicked();

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
    ProbabilitiesCalculator prob;
    QVector<Symbol> orderOneSymbols;
    QVector<Symbol> orderNSymbols;
    About aboutWindow;
    NExtension nExtensionWindow;
};

#endif // MAINWINDOW_H
