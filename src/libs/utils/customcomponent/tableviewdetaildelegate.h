#pragma once

#include <QTableView>
#include <QTouchEvent>
#include <QStyledItemDelegate>
#include "customcomponent_global.h"

class QTextBrowser;
class TableView;
class CUSTOMCOMPONENT_EXPORT TableViewDetailDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    using QStyledItemDelegate::QStyledItemDelegate;
    explicit TableViewDetailDelegate(TableView *parent, int coulmn);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;
    QTextBrowser *m_widget = 0;
    void resizeAndMoveTextBrower(const QRect &indexRect);
private:
    TableView *m_view = NULL;
    int m_column = -1;
    bool m_once = true;
    int m_isInMove = 0;

};
