#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include "customcomponent_global.h"

#include <QStyledItemDelegate>

// 自定义单行输入框委托：用于QTableView的单元格编辑
class CUSTOMCOMPONENT_EXPORT LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT // Qt信号槽必须的宏

public:
    // 构造函数
    explicit LineEditDelegate(QObject *parent = nullptr);

    // 重写QStyledItemDelegate的纯虚函数/虚函数

    // // 创建编辑器控件
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 设置编辑器的数据
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // 将编辑器的数据提交到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private slots:
    // 编辑完成的槽函数
    void slotEditingFinished();
};

#endif // LINEEDITDELEGATE_H
