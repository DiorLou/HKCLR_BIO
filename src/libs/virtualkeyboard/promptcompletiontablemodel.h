#pragma once
#include <QStandardItemModel>
#include <QThread>
#include <QQueue>
#include "virtualkeyboard_global.h"

class ProcessDataThread;
class QTableView;

class VIRTUALKEYBOARD_EXPORT PromptCompletionTableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    PromptCompletionTableModel(QTableView *parent = nullptr);

    QModelIndex index(
        int row, int column, const QModelIndex &parent = QModelIndex())
        const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    // 返回模型索引的编辑方式
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addOneCommad(const QString &str);
    // void operationWhenShow(QList<QString> *address, QString currentStr = "",QString selectMode = "");
    void setDataSource(QString headerStr,
                       QSet<QString> *dataSource,
                       QStringList removeList = QStringList(),
                       QString currentStr = "",
                       QString selectMode = "");
    void setShowData(QSet<QString> *dataSource);
    void operationWhenHide();
    QList<QString *> m_datas;
public slots:

public slots:
    void slot_refreshValues(const QObject *obj, QList<QString *> address);

private:
    QHash<int, QByteArray> m_roleNames = {{0, "display"}};
    QTableView *m_tableView;

    int m_currentDepth = 0;
    QList<QString *> *m_qstringSource;
    QList<QSet<QString *>> m_setAllRes;
    QList<QList<QString *>> m_vectorAllRes;
    QList<QList<QList<QString *>>> m_datasMap;
    QList<QList<QString *>> m_empty;
    QString m_oldStr;
    QString m_newStr;
    QSet<QString> *m_lastDataSource;
    QStringList m_headerData;
    bool m_isShow = false;
    bool m_isConnected = false;
    bool m_objectChanged = false;
    int m_rowCount = 0;
    int m_columnCount = 0;
    QList<QString *> m_currentDatas;

    //获取列名
    QString getColumnHeaderInModel(const int &column);
    QVariant getData(const QModelIndex &index, int role);

    // int m_tempCount = 0;
};
