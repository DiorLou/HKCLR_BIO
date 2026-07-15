#pragma once

#include <QAbstractButton>
#include <QPushButton>
#include "customcomponent_global.h"
class QPropertyAnimation;

class CUSTOMCOMPONENT_EXPORT SwitchButton :public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(double percent READ getPrecent WRITE setPercent)

public :
    SwitchButton(QWidget *parent);
    ~SwitchButton();
    void setLineWidth(int width);
    int getLineWidth();

    // void setEnableColor(QColor color);
    // QColor getEnableColor();

    // void setDisEnableColor(QColor color);
    // QColor getDisEnableColor();

    void setCheckable(bool);
    bool isCheckable() const;

    void setFont(QFont font);

    void reverseCheckedState();

public Q_SLOTS:
    void setEnabled(bool);
    void setChecked(bool);
    void slot_shieldCheckedFromClick(bool checked);
protected:
    void paintEvent(QPaintEvent *ev);
    void resizeEvent(QResizeEvent *ev);
    void showEvent(QShowEvent *ev);
private:
    enum CheckedState{
        UnChecked = 0,
        WaitingNextState,
        Checked,
    };
    void setAnimationState(bool state);
    QPropertyAnimation *animation;
    void setPercent(double value);
    double getPrecent();

    void updateColor();

    bool m_targetChecked  = false;
    bool m_slideChecked = false;

    bool m_isChecked  = false;
    double m_percent = 0;
    void calLocation();

    QRect m_onSize;
    QRect m_offSize;
    QRect m_leftArc;
    QRect m_rightArc;
    QPoint m_topLineStart;
    QPoint m_topLineEnd;
    QPoint m_bottomLineStart;
    QPoint m_bottomLineEnd;
    QRect m_slideArc;
    int m_slideArcStart;
    int m_slideArcEnd;
    int m_slideRange;
    int m_lineWidth;
    int m_slideArcRadius;
    QColor m_enableFontColor = QColor(20,20,20);
    QColor m_disenableFontColor = QColor(191,191,191);;
    QColor m_currentFontColor = m_enableFontColor;

    QColor m_checkedBackGroundColor = QColor::fromRgb(39,182,123);
    QColor m_uncheckedBackGroundColor = QColor::fromRgb(167,177,188);

    int m_rOffsetEnable = m_checkedBackGroundColor.red()
                        - m_uncheckedBackGroundColor.red();
    int m_gOffsetEnable = m_checkedBackGroundColor.green()
                        - m_uncheckedBackGroundColor.green();
    int m_bOffsetEnable = m_checkedBackGroundColor.blue()
                        - m_uncheckedBackGroundColor.blue();

    QColor m_disEnableCheckedBackGroundColor = QColor::fromRgb(169,226,202);
    QColor m_disEnableUncheckBackGroundColor = QColor::fromRgb(207,207,223);
    int m_rOffsetDisEnable = m_disEnableCheckedBackGroundColor.red()
                        - m_disEnableUncheckBackGroundColor.red();
    int m_gOffsetDisEnable = m_disEnableCheckedBackGroundColor.green()
                        - m_disEnableUncheckBackGroundColor.green();
    int m_bOffsetDisEnable = m_disEnableCheckedBackGroundColor.blue()
                        - m_disEnableUncheckBackGroundColor.blue();

    QColor m_currentBackGroundColor = m_uncheckedBackGroundColor;
    QTimer *m_timerUpdate;
    int m_timerCount = 0;
    // QColor m_enableBackGround = QColor::fromRgb(39,182,123);
    // QBrush m_brush;
};


