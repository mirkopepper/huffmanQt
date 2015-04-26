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
    QVector< QPair<int, int> > getData();
private:
    QImage image;
    QVector< QPair<int, int> > data;
};

#endif // IMAGEANALYZER_H
