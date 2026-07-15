#pragma once

#include <QObject>
#include <QString>
#include "authority_global.h"

class Authority;
class FuncAuthority;
class PluginAuthority;
class QXmlStreamReader;
class QXmlStreamWriter;

class AUTHORITY_EXPORT XmlHandler : public QObject
{
    Q_OBJECT
public:
    static XmlHandler *instance();
    virtual ~XmlHandler();

    bool readAuthorityFile(
        const QString &sFilePath, QString &version, Authority &curAuthority,
        QMap<Authority, QVector<PluginAuthority>> &authorities, QString &msg);

    bool writeAuthorityFile(
        const QString &sFilePath, const QString &version,
        const Authority &curAuthority,
        const QMap<Authority, QVector<PluginAuthority>> &authorities, QString &msg);

private:
    XmlHandler();

    void readVersion(QString &version);
    void readAuthority(Authority &authority);
    void readAuthorities(QMap<Authority, QVector<PluginAuthority>> &authorities);
    void readAllPluginAuthorities(QVector<PluginAuthority> &vecPluginAuthorities);
    void readPluginAuthority(PluginAuthority &pluginAuthority);
    void readFuncAuthority(FuncAuthority &funcAuthority);

    void writeVersion(const QString &version);
    void writeCurrentAuthority(const Authority &curAuthority);
    void writeAllAuthorites(const QMap<Authority, QVector<PluginAuthority> > &authorities);
    void writeAllPluginAuthorities(const QVector<PluginAuthority> &vecPluginAuthorities);
    void writePluginAuthority(const PluginAuthority &pluginAuthority);
    void writeAllFuncAuthorities(const QVector<FuncAuthority> &funcAuthorities);
    void writeFuncAuthority(const FuncAuthority &funcAuthority);

private:
    QXmlStreamReader *m_xmlReader;
    QXmlStreamWriter *m_xmlWriter;

};
