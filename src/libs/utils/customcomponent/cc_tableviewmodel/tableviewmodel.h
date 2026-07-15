#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include "customcomponent_global.h"
#include "cc_define/valuestructdefine.h"
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT TableViewModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged FINAL)

    // 接口
public:
    TableViewModel(QTableView *parent);

    ~TableViewModel();

    void initDatas(const QVector<CustomColumnMsg> &Msg,
                   const QString &name,
                   int rowCount);

    void setEnableEditFlagWhenConnect(bool enable);

    void setEditingMsg(bool editing, const QModelIndex &index);

    bool getIsInEditing();

    bool resetDatas(const QVector<QVector<QVariant>> &datas);

    bool resetDatas(const int col,
                    const QVector<int> &index,
                    const QVector<QVariant> &datas);

    QVector<QVariant>* getColValuesAddress(int col);

    QVector<QVector<QVariant>>* getAllValuesAddress();

    void retranslateHeader(const QStringList &newHeader);

signals:
    void rowCountChanged();

    void needSaveDatas(const QModelIndex &index,const QVariant &value);

private:
    QVector<QVector<QVariant>> m_datas;
    QVector<CustomColumnMsg> m_colMsg;
    int m_rowCount = 0;
    int m_columnCount = 0;
    bool m_EnableEditFlagWhenConnect = false;
    bool m_isEditing = false;
    int m_formatAlignment = 0;
    int m_place = 0;
    QString m_name;
    QModelIndex m_editingIndex;
    QTableView *m_tableView;
    QHash<int, QByteArray> m_roleNames = {{0, "display"}};
    void initDatas();

    // 重写虚函数
public:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    // 返回模型索引的编辑方式
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role = Qt::EditRole) override;
    // QHash<int, QByteArray> roleNames() const override;
    void removeRow(int rowIndex, int rows = 1);

    QString getColumnHeader(const int &column) const;
    bool IsIndexInRange(const QModelIndex &index);

    bool IsNeedShowCheckBox(const QModelIndex &index) const;
};

