#ifndef LINEEDITCOMPONENT_H
#define LINEEDITCOMPONENT_H

#include "customcomponent_global.h"

#include <QFrame>

class QLineEdit;
class ValueLimit;

namespace Ui
{
class LineEditComponent;
}

class CUSTOMCOMPONENT_EXPORT LineEditComponent : public QFrame
{
    Q_OBJECT

public:

    enum LineEditType {
        LineEdit_Type,
        IntLineEdit_Type,
        DoubleLineEdit_Type
    };

    explicit LineEditComponent(LineEditType type = LineEditType::LineEdit_Type, QWidget *parent = nullptr);
    ~LineEditComponent();

    void setDisplayOnly();

    void setText(const QString &text);

    void setLineEditText(const QString &text);
    QString lineEditText();

    void setShowText(const QString &text);

    void setLineEditValueLimit(ValueLimit &limit);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sigEditFinished();

private slots:
    void on_pbn_edit_clicked();

    void slot_edit_finished();

private:
    void UpdateUI();

    void setEditVirtualKeyboards();

private:
    Ui::LineEditComponent *ui;

    LineEditType m_lineEditType = LineEditType::LineEdit_Type;
};

#endif  // LINEEDITCOMPONENT_H
