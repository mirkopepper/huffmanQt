#include "filedecompressor.h"
#include <QMap>
#include <QBuffer>

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

    std::ifstream inputFile;
    inputFile.open(filePath.toStdString().c_str(), std::ifstream::binary);

    stringstream strStream;
    strStream << inputFile.rdbuf();
    string allfile = strStream.str();

    std::string width;
    getline(strStream, width);
    std::string height;
    getline(strStream, height);
    std::string huffmancodes;
    getline(strStream, huffmancodes);
    std::string data;
    int position = width.size()+1+height.size()+1+huffmancodes.size()+1;
    allfile.erase (0,position);
    data = allfile;

    inputFile.close();

    this->width = atoi(width.c_str());
    this->height = atoi(height.c_str());
    QString mixedcodes = QString::fromUtf8( huffmancodes.data(), huffmancodes.size() );
    QStringList newHeader = mixedcodes.split("#");

    this->header = newHeader;

    this->decodificate(data);
    this->headerInterpreter();
    this->generateFile();
}

void FileDecompressor::decodificate(std::string data)
{
    QString image;
    for (uint i = 0; i < data.size(); i++) {
        char mander = data.at(i);
        char mask = 1 << 7;
        for(int e = 0; e<8; e++){
            if((mander & mask)==mask)
                image.append("1");
            else
                image.append("0");
            mander = (mander << 1);
        }
    }
    this->imagedata = image;
}

void FileDecompressor::headerInterpreter()
{
    QStringList::iterator it;
    for(it=this->header.begin(); it!=this->header.end(); it++)
    {
        this->codes.insert(it->mid(6), it->mid(0,6).prepend("#"));
    }
}

void FileDecompressor::generateFile()
{
    QString aux;
    QVector<QColor> colors;
    QString::iterator it;
    for(it=this->imagedata.begin(); it!=this->imagedata.end(); it++) {
        aux += *it;
        if(this->codes.contains(aux)) {
            colors.push_back(QColor(this->codes.find(aux).value()));
            aux.clear();
        }
    }
    QImage img(this->width, this->height, QImage::Format_RGB32);

    int k = 0;
    for(int i=0; i<this->height; i++) {
        for(int j=0; j<this->width; j++) {
            img.setPixel(j,i,colors.at(k).rgb());
            k++;
        }
    }

    QFileDialog dialog;
    QString filePath = dialog.getSaveFileName(0, ("Save File")," ", ("Images (*.bmp)"));
    /*dialog.setFileMode(QFileDialog::AnyFile);
    getSaveFileName ()
    dialog.setNameFilter("BitMap (*.bmp)");
    int result = dialog.exec();
    if (result) {
        filePath = dialog.selectedFiles().first();
        filePath.append(".bmp");
    }
    else
        filePath = "";*/

    img.save(filePath,0,100); // IMAGEN SIN COMPRESION
}

