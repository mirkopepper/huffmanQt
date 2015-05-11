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

            //creating new Symbol
            Symbol newNode;
            newNode.setColors(newSymbol);
            newNode.setProbability(newProb);
            symbols.append(newNode);

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

void ProbabilitiesCalculator::extend(int n, QVector<Symbol> &symbols)
{
    QVector<QString> tempSymbol;
    double tempProb = 1;
    backtrack(n, tempSymbol, tempProb);
    symbols = this->symbols;
    /*for (int i = 0; i < symbols.size(); i++) {
        for (int e = 0; e < symbols.at(i).size(); e++) {
            qDebug() << symbols.at(i).at(e);
        }
        qDebug() << " " << symbProbs.at(i);
    }*/
}
