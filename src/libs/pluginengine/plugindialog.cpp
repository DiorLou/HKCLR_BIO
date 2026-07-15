#include "plugindialog.h"

#include <pluginmanager.h>
#include <pluginview.h>
#include <plugindetailsview.h>
#include <pluginerrorview.h>
#include <pluginspec.h>

#include <fancylineedit.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

using namespace PluginEngine;

static bool s_isRestartRequired = false;

PluginDialog::PluginDialog(QWidget *parent) :
    QDialog(parent),
    m_view(new PluginEngine::PluginView(this))
{
    QVBoxLayout *vl = new QVBoxLayout(this);

    auto filterEdit = new Utils::FancyLineEdit(this);
    filterEdit->setFiltering(true);
    connect(filterEdit, &Utils::FancyLineEdit::filterChanged,
            m_view, &PluginEngine::PluginView::setFilter);
    vl->addWidget(filterEdit);

    vl->addWidget(m_view);

    m_detailsButton = new QPushButton(tr("Details"), this);
    m_errorDetailsButton = new QPushButton(tr("Error details"), this);
    m_closeButton = new QPushButton(tr("Close"), this);
    m_detailsButton->setEnabled(false);
    m_errorDetailsButton->setEnabled(false);
    m_closeButton->setEnabled(true);
    m_closeButton->setDefault(true);

    m_restartRequired = new QLabel(tr("Restart required."), this);
    if (!s_isRestartRequired)
        m_restartRequired->setVisible(false);

    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget(m_detailsButton);
    hl->addWidget(m_errorDetailsButton);
    hl->addSpacing(10);
    hl->addWidget(m_restartRequired);
    hl->addStretch(5);
    hl->addWidget(m_closeButton);

    vl->addLayout(hl);

    resize(650, 400);
    setWindowTitle(tr("Installed plugins"));

    connect(m_view, &PluginEngine::PluginView::currentPluginChanged,
            this, &PluginDialog::updateButtons);
    connect(m_view, &PluginEngine::PluginView::pluginActivated,
            this, &PluginDialog::openDetails);
    connect(m_view, &PluginEngine::PluginView::pluginSettingsChanged,
            this, &PluginDialog::updateRestartRequired);
    connect(m_detailsButton, &QAbstractButton::clicked,
            [this] { openDetails(m_view->currentPlugin()); });
    connect(m_errorDetailsButton, &QAbstractButton::clicked,
            this, &PluginDialog::openErrorDetails);
    connect(m_closeButton, &QAbstractButton::clicked,
            this, &PluginDialog::closeDialog);
    updateButtons();
}

void PluginDialog::closeDialog()
{
    PluginEngine::PluginManager::writeSettings();
    accept();
}

void PluginDialog::updateRestartRequired()
{
    // just display the notice all the time after once changing something
    s_isRestartRequired = true;
    m_restartRequired->setVisible(true);
}

void PluginDialog::updateButtons()
{
    PluginEngine::PluginSpec *selectedSpec = m_view->currentPlugin();
    if (selectedSpec) {
        m_detailsButton->setEnabled(true);
        m_errorDetailsButton->setEnabled(selectedSpec->hasError());
    } else {
        m_detailsButton->setEnabled(false);
        m_errorDetailsButton->setEnabled(false);
    }
}

void PluginDialog::openDetails(PluginEngine::PluginSpec *spec)
{
    if (!spec)
        return;
    QDialog dialog(this);
    dialog.setWindowTitle(tr("%1 plugin details").arg(spec->name()));
    QVBoxLayout *layout = new QVBoxLayout;
    dialog.setLayout(layout);
    PluginEngine::PluginDetailsView *details = new PluginEngine::PluginDetailsView(&dialog);
    layout->addWidget(details);
    details->update(spec);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal, &dialog);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.resize(400, 500);
    dialog.exec();
}

void PluginDialog::openErrorDetails()
{
    PluginEngine::PluginSpec *spec = m_view->currentPlugin();
    if (!spec)
        return;
    QDialog dialog(this);
    dialog.setWindowTitle(tr("%1 plugin error").arg(spec->name()));
    QVBoxLayout *layout = new QVBoxLayout;
    dialog.setLayout(layout);
    PluginEngine::PluginErrorView *errors = new PluginEngine::PluginErrorView(&dialog);
    layout->addWidget(errors);
    errors->update(spec);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal, &dialog);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.resize(500, 300);
    dialog.exec();
}
