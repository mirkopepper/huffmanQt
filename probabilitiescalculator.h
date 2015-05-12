#ifndef PROBABILITIESCALCULATOR_H
#define PROBABILITIESCALCULATOR_H

#include <QVector>
#include <QPair>
#include <QDebug>
#include "symbol.h"

class ProbabilitiesCalculator
{
public:
    ProbabilitiesCalculator();
    QVector<Symbol> calculate(const QVector< QPair<QString, int> > &colorCount, int total);
    void extend(int n, QVector<Symbol> &symbols);
    void backtrack(int n, QVector<QString> newSymbol, double newProb);
    void backtrackNoRecursion(int n);
    QVector< QPair<QString, double> > getProbabilities();
private:
     QVector< QPair<QString, double> > probs;
     QVector<Symbol> symbols;

};

#endif // PROBABILITIESCALCULATOR_H
