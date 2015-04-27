#include "huffmanalgorithm.h"
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <algorithm>

HuffmanAlgorithm::HuffmanAlgorithm()
{

}

void HuffmanAlgorithm::setData(QVector< QPair<QString, double> > p)
{
    this->probabilities = p;
}

void HuffmanAlgorithm::run()
{
    this->sortProbabilities();
    QVector<Node> list = convert();
    while (list.size() > 1)
    {
        Node * node1 = new Node;
        *node1 = list.takeLast();
        node1->code = 0;
        Node * node2 = new Node;
        *node2 = list.takeLast();
        node2->code = 1;
        Node * newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->code = NULL;
        newNode->probability = node1->probability + node2->probability;
        newNode->left = node1;
        newNode->right = node2;

        insert(list, *newNode);
    }
    generateCode(list.takeFirst(), "");
    qDebug() << solution;

}

void HuffmanAlgorithm::insert(QVector<Node> & list, Node n)
{
    bool found = false;
    QVector<Node>::iterator it = list.begin();
    while(it!=list.end() && !found)
    {
        if(it->probability < n.probability )
        {
            list.insert(it,1,n);
            found = true;
        }
        it++;
    }
    if (!found)
            list.push_back(n);
}

void HuffmanAlgorithm::generateCode(Node n, QString huffcode)
{
    if (n.left != NULL) {
        Node *nodeleft= n.left;
        Node *noderight= n.right;
        QString cLeft = QString::number(nodeleft->code);
        QString cRight = QString::number(noderight->code);
        QString huffcodeLeft;
        huffcodeLeft.append(huffcode);
        QString huffcodeRight;
        huffcodeRight.append(huffcode);
        huffcodeLeft.append(cLeft);
        huffcodeRight.append(cRight);
        generateCode(*n.left, huffcodeLeft);
        generateCode(*n.right, huffcodeRight);
    }
    else {
        solution.push_back(qMakePair(n.symbol, huffcode));
    }

}

QVector<Node> HuffmanAlgorithm::convert()
{
    QVector<Node> result;
    QVector< QPair<QString, double> >::iterator it;
    for(it=this->probabilities.begin(); it!=this->probabilities.end(); it++)
    {
        Node *aux = new Node;
        aux->symbol = it->first;
        aux->probability = it->second;
        aux->left = NULL;
        aux->right = NULL;
        result.push_back(*aux);
    }
    return result;
}

void HuffmanAlgorithm::sortProbabilities()
{
    qSort(probabilities.begin(), probabilities.end(), Comparator());
}

double HuffmanAlgorithm::getAverageLength(QVector< QPair<int, double> > codes)
{
    double sum = 0;
    QVector< QPair<int, double> >::iterator it;
    for(it=codes.begin(); it!=codes.end(); it++)
    {
        sum+= it->second * qLn(1/ it->first) /qLn(2);
    }
    return sum;
}

double HuffmanAlgorithm::getEntropy()
{
    double sum = 0;
    QVector< QPair<QString, double> >::iterator it;
    for(it=this->probabilities.begin(); it!=this->probabilities.end(); it++)
    {
        sum+= it->second * qLn(1/ it->second)/qLn(2);
    }

    return sum;
}

double HuffmanAlgorithm::getPerformance()
{
    return this->getEntropy()/this->getAverageLength();
}

QVector< QPair<QString, QString> > HuffmanAlgorithm::getCodes()
{
    return this->solution;
}
