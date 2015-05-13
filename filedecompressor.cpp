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
    inputFile.open(QIODevice::ReadOnly);

    /* Check it opened OK */
    if(!inputFile.isOpen()){
        qDebug() << "- Error, unable to open" << filePath << "for input";
    }

    /* Point a QTextStream object at the file */
    QTextStream inStream(&inputFile);

    /* Write the line to the file */

    QString text = inStream.readAll();


    /* Close the file */
    inputFile.close();

    QStringList list = text.split(" ");
    this->width = list.at(0).toInt();
    this->height = list.at(1).toInt();
    this->imagedata;
    QStringList codelist = list.at(2).split("#");
    this->header = codelist;
}

void FileDecompressor::decodificate()
{

}

void FileDecompressor::calculateHeader()
{

}

void FileDecompressor::generateFile()
{

}

