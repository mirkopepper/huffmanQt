#include "filedecompressor.h"



FileDecompressor::FileDecompressor()
{

}

FileDecompressor::~FileDecompressor()
{

}

void FileDecompressor::decompress()
{
    //Opens HZIP file
    qDebug() << endl << endl;
    QString filePath;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("HuffmanZip (*.hzip)");
    int result = dialog.exec();
    if (result)
        filePath = dialog.selectedFiles().first();
    else
        filePath = "";
    //Now we need to separate HEADER from DATA

    QFile inputFile(filePath);
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    /* Check it opened OK */
    if(!inputFile.isOpen()){
        qDebug() << "- Error, unable to open" << filePath << "for input";
    }

    /* Point a QTextStream object at the file */
    QTextStream inStream(&inputFile);

    /* Write the line to the file */
    qDebug() << "????????????????????????????????";
    QString text = inStream.readAll();

    /* Close the file */
    inputFile.close();

    QStringList list = text.split(" ",QString::SkipEmptyParts);
    this->width = list.at(0).toInt();
    this->height = list.at(1).toInt();
    this->imagedata = list.at(3);
    QStringList codelist = list.at(2).split("#");
    this->header = codelist;

    decodificate();
}

void FileDecompressor::decodificate()
{
    QString file = this->imagedata;
    std::string filestring = file.toStdString();
    char temp = filestring.at(0);
    qDebug() << "EL PRIMER CHAR SIN DECODIFICAR ES" <<temp;
    QChar temp2 = filestring.at(0);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp2;
    qDebug() << "EL UNICODE: " << temp2.unicode();
    QChar temp3 = filestring.at(1);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp3;
    qDebug() << "EL UNICODE: " << temp3.unicode();

    QString image;


    for (int i = 0; i < file.size(); i++) {
        char mander = filestring.at(i);
        for (int e = 0; e < 16; e++) {
            int value = (e >> mander) & 1;
            qDebug() << value;
            image.append(value);
        }
    }
    qDebug() << image.at(0) << image.at(1);


}

void FileDecompressor::headerInterpreter()
{

}

void FileDecompressor::generateFile()
{

}

