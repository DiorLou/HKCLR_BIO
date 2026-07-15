#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include "customcomponent_global.h"

#include <QStyledItemDelegate>
#include "combobox.h"

class CUSTOMCOMPONENT_EXPORT ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr, bool isEmitSignal = true);

    // // 创建编辑器控件
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 设置编辑器的数据
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // 将编辑器的数据提交到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

Q_SIGNALS:
    void sigEditorCreated(int, int, ComboBox *) const;
    void signal_index_active(QWidget *editor, int index);

private slots:
    void slotActivated(int index);

private:
    bool m_isEmitSignal = true;
};

#endif // COMBOBOXDELEGATE_H
