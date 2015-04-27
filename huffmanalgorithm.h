#ifndef HUFFMANALGORITHM_H
#define HUFFMANALGORITHM_H

#include <QVector>
#include <QString>
#include <QPair>

struct Node
{
    int code;
    double probability;
    QString symbol;
    Node *left;
    Node *right;
};

class HuffmanAlgorithm
{
public:
    HuffmanAlgorithm();
    void setData(QVector< QPair<QString, double> > p);
    void run();
    double getAverageLength();
    double getPerformance();
    double getEntropy();
    QVector< QPair<double, QString> > getCodes();
private:
    void sortProbabilities();
    void generateCode(Node n, QString huffcode);
    void insert(QVector<Node> list, Node n);
    QVector< QPair<QString, double> > probabilities;
    QVector< QPair<double, QString> > codes;
    QVector< QPair<QString, QString> > solution;
    QVector<Node> convert();
    struct Comparator
    {
        template<typename T1, typename T2>
        bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
        {
            return a.second < b.second;
        }
    };
};

#endif // HUFFMANALGORITHM_H
