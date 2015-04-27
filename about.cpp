#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QString textToShow = "Este programa fue realizado como trabajo de cursada para la materia Teoría de la Información por Mirko Hrubik y Andrés Chardon. \n";
    textToShow.append("\n El objetivo del programa es, dada una imagen, obtener las probabilidades asociadas a cada color en ella, y su codificación Huffman asociada.");
    ui->infoBox->setText(textToShow);
}

About::~About()
{
    delete ui;
}
