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
    QVector<QString> toVector();
    int getTotalPixels();
    int getHeight() const;
    int getWidth() const;
private:
    QImage image;
    QVector< QPair<QString, int> > ColorCount;
    int totalPixels;
    int height;
    int width;
};

#endif // IMAGEANALYZER_H
