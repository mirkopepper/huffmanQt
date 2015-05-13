#ifndef HUFFMANALGORITHM_H
#define HUFFMANALGORITHM_H

#include <QVector>
#include <QString>
#include <QPair>
#include "symbol.h"

struct Node
{
    int code;
    double probability;
    QVector<QString> symbol;
    Node *left;
    Node *right;
};

class HuffmanAlgorithm
{
public:
    HuffmanAlgorithm();
    void calculateHuffman(QVector<Symbol> &symbols);
    double getAverageLength();
    double getPerformance();
    double getEntropy();
    QVector<Symbol> getSolution();
private:
    void sortByProbs();
    void generateCode(Node n, QString huffcode);
    void insert(QVector<Node> & list, Node n);
    QVector<Symbol> symbols;
    QVector<Node> convert();
    struct Comparator
    {
        template<typename T1, typename T2>
        bool operator()(const T1 & a, const T2 & b) const
        {
            return a.getProbability() > b.getProbability();
        }
    };
};

#endif // HUFFMANALGORITHM_H
