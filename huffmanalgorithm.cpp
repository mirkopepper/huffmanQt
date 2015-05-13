#include "huffmanalgorithm.h"
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <algorithm>

HuffmanAlgorithm::HuffmanAlgorithm()
{

}


void HuffmanAlgorithm::calculateHuffman(QVector<Symbol> &symbols)
{
    //INICIALIZAR
    this->symbols = symbols;
    //ORDENAR
    sortByProbs();
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
        //newNode->code = NULL;
        newNode->probability = node1->probability + node2->probability;
        newNode->left = node1;
        newNode->right = node2;

        insert(list, *newNode);
    }
    generateCode(list.takeFirst(), "");
    qDebug() << "YA TERMINOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    symbols = this->symbols;
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
        int i = 0;
        bool found = false;
        while (i < symbols.size() && !found) {
            if (symbols.at(i).getColors() == n.symbol) {
                Symbol newSymbol;
                newSymbol = symbols.at(i);

                newSymbol.setHuffmanCode(huffcode);

                symbols.replace(i, newSymbol);
                qDebug() << symbols.at(i).getHuffmanCode();
                found = true;
            }
            i++;
        }
    }
}

QVector<Node> HuffmanAlgorithm::convert()
{
    QVector<Node> result;
    QVector<Symbol>::iterator it;
    for(it=this->symbols.begin(); it!=this->symbols.end(); it++)
    {
        Node *aux = new Node;
        aux->symbol = it->getColors();
        aux->probability = it->getProbability();
        aux->left = NULL;
        aux->right = NULL;
        result.push_back(*aux);
    }
    return result;
}

void HuffmanAlgorithm::sortByProbs()
{
    qSort(symbols.begin(), symbols.end(), Comparator());
}

double HuffmanAlgorithm::getAverageLength()
{
    double sum = 0;
    QVector<Symbol>::iterator it;
    for(it=this->symbols.begin(); it!=this->symbols.end(); it++)
    {
        sum += it->getProbability();
    }
    return sum;
}

double HuffmanAlgorithm::getEntropy()
{
    double sum = 0;
    QVector<Symbol>::iterator it;
    for(it=this->symbols.begin(); it!=this->symbols.end(); it++)
    {
        sum += it->getProbability() * qLn(1/ it->getProbability())/qLn(2);
    }

    return sum;
}

double HuffmanAlgorithm::getPerformance()
{
    return this->getEntropy()/this->getAverageLength();
}

QVector<Symbol> HuffmanAlgorithm::getSolution()
{
    return this->symbols;
}
