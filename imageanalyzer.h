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
     QVector< QPair<QString, int> > getData();
private:
    QImage image;
     QVector< QPair<QString, int> > data;
};

#endif // IMAGEANALYZER_H
