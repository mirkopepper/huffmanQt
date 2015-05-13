#include "filecompressor.h"

FileCompressor::FileCompressor()
{

}

FileCompressor::~FileCompressor()
{

}

void FileCompressor::codificate()
{

}

QString FileCompressor::calculateHeader(QVector<Symbol> codes, int height, int width)
{
    QString tempString;
    tempString.append(QString::number(width));
    tempString.append(" ");
    tempString.append(QString::number(height));
    tempString.append(" ");
    for (int i = 0; i < codes.size(); i++) {
        tempString.append(codes.at(i).getHuffmanCode());
        tempString.append(codes.at(i).getColors().at(0));

    }
    tempString.append(" ");
    return tempString;
}

void FileCompressor::compress(QVector<Symbol> codes, QVector<QString> image, int height, int width)
{
    //calculo el header en un QString para agregar al archivo de salida
    QString header = calculateHeader(codes, height, width);
    qDebug() << header;
    //codifico segun huffman la imagen en un QString (a nivel bit)
    codificate();
    //genero el archivo de texto de salida
}
