#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QString>
#include <QImage>
#include <QDebug>
#include <QRgb>
#include <QColor>

class ImageAnalyzer
{
public:
    ImageAnalyzer();
    void start(QString filePath);
    QVector< QPair<QString, int> > getColorCount();
    int getTotalPixels();
private:
    QImage image;
    QVector< QPair<QString, int> > ColorCount;
    int totalPixels;
};

#endif // IMAGEANALYZER_H
