#pragma once

#include <QDialog>
#include "customcomponent_global.h"

namespace Ui {
class MaskWidget;
}

class CUSTOMCOMPONENT_EXPORT MaskWidget : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QStringList names READ names WRITE setNames DESIGNABLE true)
public:
    static MaskWidget *instance();

    void setMainWidget(QWidget* widget);

    QStringList names() const;
    void setNames(const QStringList& names);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    explicit MaskWidget(QWidget *parent = 0);
    virtual ~MaskWidget();

private:
    Ui::MaskWidget *ui;

    QStringList m_listName;

    QWidget* m_mainWidget;

};
