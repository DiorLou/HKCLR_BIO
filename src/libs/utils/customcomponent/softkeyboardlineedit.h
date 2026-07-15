#include <QLineEdit>
#include <QObject>
#include <QString>
#include <QList>
#include "customcomponent_global.h"
class CUSTOMCOMPONENT_EXPORT SoftKeyBoardLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    // //地址操作
    Q_PROPERTY(QList<QString>* sourceQStringListAddress
                   MEMBER m_sourceQStringListAddress
                       READ getSourceQStringListAddress)

    // //数据操作
    // Q_PROPERTY(QList<QString> sourceQStringList
    //                MEMBER m_sourceQStringList
    //                    READ getSourceQStringList
    //                        WRITE getSourceQStringList)
    explicit SoftKeyBoardLineEdit(QWidget *parent = nullptr);
    QList<QString>* getSourceQStringListAddress();
    //void setSourceQStringListAddress(QList<QString>* list);

    QList<QString> getSourceQStringList();
    void setSourceQStringList(QList<QString> list);
signals:

private:
    QList<QString> *m_sourceQStringListAddress;
    QStringList m_sourceQStringList;

};
