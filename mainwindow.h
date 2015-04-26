#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include "imageanalyzer.h"

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

    ImageAnalyzer IA;
};

#endif // MAINWINDOW_H
