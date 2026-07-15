#pragma once
#include <QRadioButton>
#include <QWidget>
class VirtualKeyBoardRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit VirtualKeyBoardRadioButton(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *ev);
    QColor m_checkedIndiacatorColor = QColor::fromRgb(82,197,149);

signals:
};

