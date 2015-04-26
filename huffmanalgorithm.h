#ifndef HUFFMANALGORITHM_H
#define HUFFMANALGORITHM_H

#include <QVector>
#include <QString>
#include <QPair>

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
    QVector< QPair<QString, double> > probabilities;
    QVector< QPair<double, QString> > codes;
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
