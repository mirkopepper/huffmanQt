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
    outStream << header << data;

    /* Close the file */
    outputFile.close();

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

