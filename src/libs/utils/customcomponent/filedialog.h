#pragma once
#include "customcomponent_global.h"
#include <QWidget>
#include <QFileDialog>

class CUSTOMCOMPONENT_EXPORT FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    static QString getSaveFileName(const QString &caption = QString(),
                                   const QString &dir = QString(),
                                   const QString &filter = QString(),
                                   QString *selectedFilter = nullptr);

    static QString getOpenFileName(const QString &caption = QString(),
                                   const QString &dir = QString(),
                                   const QString &filter = QString(),
                                   QString *selectedFilter = nullptr);

    // static FileDialog *instance();
    FileDialog(QWidget *parent = nullptr);
    using FileNameCallBack = std::function<void(QString)>;
    void getOpenFileNameAsyn(
        FileNameCallBack callback,
        const QString &caption = QString(),
        const QString &dir = QString(),
        const QString &filter = QString(),
        QString *selectedFilter = nullptr,
        QFileDialog::Options options = QFileDialog::Options());

    void getSaveFileNameAsyn(
        FileNameCallBack callback,
        const QString &caption = QString(),
        const QString &dir = QString(),
        const QString &filter = QString(),
        QString *selectedFilter = nullptr,
        QFileDialog::Options options = QFileDialog::Options());

    void getExistingDirectoryAsyn(
        FileNameCallBack callback,
        const QString &caption = QString(),
        const QString &dir = QString(),
        QFileDialog::Options options = QFileDialog::Options());
};

