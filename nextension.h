#ifndef NEXTENSION_H
#define NEXTENSION_H

#include <QWidget>
#include <QString>
#include <QVector>
#include "symbol.h"

namespace Ui {
class NExtension;
}

class NExtension : public QWidget
{
    Q_OBJECT

public:
    explicit NExtension(QWidget *parent = 0);
    ~NExtension();
    void loadData(QVector<Symbol> orderNSymbols);

private:
    Ui::NExtension *ui;
};

#endif // NEXTENSION_H
