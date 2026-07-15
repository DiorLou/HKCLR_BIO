#ifndef SIMMODELWIDGET_H
#define SIMMODELWIDGET_H

#include <QWidget>
#include "simulator_global.h"


class SIMULATOR_EXPORT SimModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimModelWidget(QWidget *parent = nullptr);

signals:

private slots:
    void initOsg();

private:
    QWidget *pOsgW ;
};

#endif  // SIMMODELWIDGET_H
