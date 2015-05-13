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
    this->header = list.at(2).split("#", QString::SkipEmptyParts);
    this->headerInterpreter();
    //Tendria que quedar asi los bits que me da decodificar
    //QString bits = decodificate();
    QString bits = "1010111000010110101101011101010010101010010011110";
    this->generateFile(bits);
}

QString FileDecompressor::decodificate()
{

}

void FileDecompressor::headerInterpreter()
{
    QStringList::iterator it;
    for(it=this->header.begin(); it!=this->header.end(); it++)
    {
        this->codes.insert(it->mid(6), it->mid(0,6).prepend("#"));
    }
}

void FileDecompressor::generateFile(QString bits)
{
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
    for(int i=0; i<this->height; i++)
    {
        for(int j=0; j<this->width; j++)
        {
            img.setPixel(i,j,colors.first().rgb());
        }

    }
    //Tengo que ver como guardar la imagen
    img.save(&buffer, "PNG");
}

