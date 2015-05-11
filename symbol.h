#ifndef SYMBOL_H
#define SYMBOL_H

#include <QVector>
#include <QPair>
#include <QDebug>
#include <QString>

class Symbol
{
public:
    Symbol();

    void setColors(QVector<QString> colors);
    void addColor(QString color);
    void setProbability(double prob);
    void multiplyProbability(double newProb);
    void setHuffmanCode(QString huffcode);

    QVector<QString> getColors() const;
    double getProbability() const;
    QString getHuffmanCode() const;

private:
    QVector<QString> colors;
    double probability;
    QString huffmanCode;
};

#endif // SYMBOL_H
