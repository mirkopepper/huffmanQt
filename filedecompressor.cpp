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
    this->header = list.at(2).split("#", QString::SkipEmptyParts);
    this->imagedata = list.at(3);
    this->headerInterpreter();
    //Tendria que quedar asi los bits que me da decodificar
    //QString bits = decodificate();
    QString bits = "1010111000010110101101011101010010101010010011110";
    this->generateFile(bits);
}

QString FileDecompressor::decodificate()
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

