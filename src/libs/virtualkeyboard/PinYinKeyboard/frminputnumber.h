#ifndef FRMINPUTNUMBER_H
#define FRMINPUTNUMBER_H

#include <QWidget>
#include <QPushButton>
class frmInput;

namespace Ui {
class frmInputNumber;
}

class frmInputNumber : public QWidget
{
    Q_OBJECT

public:
    explicit frmInputNumber(QWidget *parent = 0);
    ~frmInputNumber();

private:
    Ui::frmInputNumber *ui;
    frmInput *input{nullptr};
    QList<QPushButton *> btns;

public slots:
    void setInput(frmInput *input);
    void setBtns(QList<QPushButton *> btns);
    void setSpacing(int spacing);
    void setAutoRepeat(bool autoRepeat);

    void initClicked();
    void btnClicked();
};

#endif // FRMINPUTNUMBER_H
