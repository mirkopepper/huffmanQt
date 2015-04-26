#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QString>
#include <QImage>
#include <QDebug>
#include <QRgb>

class ImageAnalyzer
{
public:
    ImageAnalyzer();
    void start(QString filePath);
    QVector<int> getData();
private:
    QImage image;
    QVector<int> data;
};

#endif // IMAGEANALYZER_H
