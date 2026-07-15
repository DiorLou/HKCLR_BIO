#ifndef PINYINCHAR_H
#define PINYINCHAR_H

#include <QPushButton>
class frmInput;

class PinYinChar : public QObject
{
    Q_OBJECT
public:
    explicit PinYinChar(QObject *parent = 0);

private:
    frmInput *input;
    QList<QPushButton *> btns;

public slots:
    void setInput(frmInput *input);
    void setBtns(QList<QPushButton *> btns);

    //改变字符类型
    void setCharType(quint8 charType, QPushButton *btnChar);
};

#endif // PINYINCHAR_H
