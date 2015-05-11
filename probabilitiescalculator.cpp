#include "probabilitiescalculator.h"

ProbabilitiesCalculator::ProbabilitiesCalculator()
{
}

void ProbabilitiesCalculator::calculate(const QVector< QPair<QString, int> > &colorCount, int total)
{
    for (int e = 0; e < colorCount.size(); e++) {
        QString first = colorCount.at(e).first;
        double second = (double)(colorCount.at(e).second)/total;
        probs.push_back(qMakePair(first, second));
    }
}

QVector< QPair<QString, double> > ProbabilitiesCalculator::getProbabilities()
{
    return probs;
}

void ProbabilitiesCalculator::backtrack(int n, QVector<QString> newSymbol, double newProb)
{
    if (n == 1) {
        for (int i=0; i < probs.size(); i++) {
            newSymbol.append(probs.at(i).first);
            newProb = newProb * (probs.at(i).second);
            symbProbs.append(newProb);
            symbols.append(newSymbol);
            newSymbol.removeLast();
            newProb = newProb / (probs.at(i).second);
        }
    }
    else {
        for (int i=0; i < probs.size(); i++) {
            newSymbol.append(probs.at(i).first);
            newProb = newProb * (probs.at(i).second);
            backtrack(n-1, newSymbol, newProb);
            newSymbol.removeLast();
            newProb = newProb / (probs.at(i).second);
        }
    }
}

void ProbabilitiesCalculator::extend(int n, QVector< QVector<QString> > &symbols, QVector<double> &symbProbs)
{
    QVector<QString> tempSymbol;
    double tempProb = 1;
    backtrack(n, tempSymbol, tempProb);
    symbols = this->symbols;
    symbProbs = this->symbProbs;
    for (int i = 0; i < symbols.size(); i++) {
        for (int e = 0; e < symbols.at(i).size(); e++) {
            qDebug() << symbols.at(i).at(e);
        }
        qDebug() << " " << symbProbs.at(i);
    }
}
