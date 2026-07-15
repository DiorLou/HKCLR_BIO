#pragma once
#include <QFrame>
#include "customcomponent_global.h"

#ifdef INOCOBOTTP_MSVC_QT5
    #include <QSet>
    #include <QString>
#endif
class QLabel;
class QLineEdit;
class QPushButton;
class ComboBox;

class CUSTOMCOMPONENT_EXPORT SearchBox : public QFrame
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);
    virtual ~SearchBox();

    void updateSearchResult(int result, int pos = 0, bool isVisible = true);
    void autoGotoNext();

    void addSearchTypes(const QStringList &types);

    void retranslateUi();

    QString currentSearchType();

    void updateSearchDataOptions(const char *property, QSet<QString> *datas);

Q_SIGNALS:
    void signal_typeChanged();
    void signal_propertyChanged(QObject *object);

    void signal_search(const QString &text);
    void signal_locateResult(int index);

private:
    void initUi();

public Q_SLOTS:
    void slot_clearSearchInfo();

private Q_SLOTS:
    void slot_search(const QString &text);
    void slot_gotoPrev();
    void slot_gotoNext();

private:
    ComboBox *m_combSearchType;
    QLineEdit *m_leSearch;
    QLabel *m_lblSearchResult;
    QPushButton *m_pbnPrev;
    QPushButton *m_pbnNext;

    int m_curPos;
    int m_total;
};
