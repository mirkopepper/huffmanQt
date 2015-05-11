#include "symbol.h"

Symbol::Symbol()
{
}

void Symbol::setColors(QVector<QString> colors)
{
    this->colors = colors;
}

void Symbol::addColor(QString color)
{
    this->colors.append(color);
}

void Symbol::setProbability(double prob)
{
    this->probability = prob;
}

void Symbol::multiplyProbability(double newProb)
{
    this->probability = this->probability * newProb;
}

void Symbol::setHuffmanCode(QString huffcode)
{
    this->huffmanCode = huffcode;
}

QVector<QString> Symbol::getColors() const
{
    return this->colors;
}

double Symbol::getProbability() const
{
    return this->probability;
}
QString Symbol::getHuffmanCode() const
{
    return this->huffmanCode;
}
