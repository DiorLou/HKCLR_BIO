#ifndef RADIOBUTTONDELEGATE_H
#define RADIOBUTTONDELEGATE_H

#include "customcomponent_global.h"

#include <QStyledItemDelegate>

class CUSTOMCOMPONENT_EXPORT RadioButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RadioButtonDelegate(QObject *parent = nullptr);

    // // 创建编辑器控件
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 设置编辑器的数据
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // 将编辑器的数据提交到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private slots:
    void slotStateChanged(bool bChecked = false);
};

#endif // RADIOBUTTONDELEGATE_H
