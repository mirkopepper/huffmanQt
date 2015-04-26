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
private:
    QImage image;
};

#endif // IMAGEANALYZER_H
