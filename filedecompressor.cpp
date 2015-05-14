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

    std::ifstream inputFile;
    inputFile.open(filePath.toStdString());

    std::string width;
    getline(inputFile, width);
    std::string height;
    getline(inputFile, height);
    std::string huffmancodes;
    getline(inputFile, huffmancodes);
    std::string data;
    getline(inputFile, data);
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

QString FileDecompressor::decodificate(std::string data)
{
    QString image;
    for (int i = 0; i < data.size(); i++) {
        char mander = data.at(i);
        char mask = 1 << 7;//desplaza el 1, 7 lugares a la izq (32768)
        for(int e = 0; e<8; e++){
            if((mander & mask)==mask)
                image.append("1");
            else
                image.append("0");
            mander = (char) (mander << 1);
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
    QString bits = this->imagedata;
    QString aux;
    QVector<QColor> colors;
    QString::iterator it;
    for(it=bits.begin(); it!=bits.end(); it++)
    {
        aux += *it;
        if(this->codes.contains(aux))
        {
            colors.push_back(QColor(this->codes.find(aux).value()));
            aux.clear();
        }
    }
    qDebug() << colors;
    QImage img;
    QByteArray ba;
    QBuffer buffer(&ba);
    //Esto va a tardar por la resolucion de la imagen, no es que se colgo el programa
    int k = 0;
    for(int i=0; i<this->height; i++)
    {
        for(int j=0; j<this->width; j++)
        {
            //Por cada pixel asigno un valor del Map. Deberia haber la misma cantidad de pixeles que tamaño del map.
            img.setPixel(i,j,colors.at(k).rgb());
            k++;
        }

    }
    //Tengo que ver como guardar la imagen
    img.save(&buffer, "PNG");
}

