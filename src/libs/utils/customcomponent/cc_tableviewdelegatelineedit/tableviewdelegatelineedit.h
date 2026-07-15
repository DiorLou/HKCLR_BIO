#pragma once

#include <QItemDelegate>
#include "customcomponent_global.h"
#include "cc_define/valuestructdefine.h"
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT TableViewDelegateLineEdit: public QItemDelegate
{
       Q_OBJECT
public:

    TableViewDelegateLineEdit(ValueLimit _ValueLimit,
                              QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;
private:
    ValueLimit m_valueLimit;
};

