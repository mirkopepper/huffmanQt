#ifndef PROBABILITIESCALCULATOR_H
#define PROBABILITIESCALCULATOR_H

#include <QVector>
#include <QPair>
#include <QDebug>

class ProbabilitiesCalculator
{
public:
    ProbabilitiesCalculator();
    void calculate(const QVector< QPair<QString, int> > &colorCount, int total);
    void extend(int n, QVector< QVector<QString> > &symbols, QVector<double> &symbProbs);
    void backtrack(int n, QVector<QString> newSymbol, double newProb);
    QVector< QPair<QString, double> > getProbabilities();
private:
     QVector< QPair<QString, double> > probs;
     QVector< QVector<QString> > symbols;
     QVector<double> symbProbs;

};

#endif // PROBABILITIESCALCULATOR_H
