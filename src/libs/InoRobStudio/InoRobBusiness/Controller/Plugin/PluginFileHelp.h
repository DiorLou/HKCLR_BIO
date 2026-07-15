#pragma once

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include <QDir>
#include <QFileInfo>

#include <QTextCodec>

class PluginFileHelp
{
public:
static  QByteArray gb2312ToUtf8(const QByteArray& gb2312) 
{
        QTextCodec* codec = QTextCodec::codecForName("GB2312");
        QTextCodec* utf8Codec = QTextCodec::codecForName("UTF-8");
        QString unicode = codec->toUnicode(gb2312);
        QByteArray utf8 = utf8Codec->fromUnicode(unicode);
        return utf8;
}
static bool readFile(const QString& filePath, QByteArray& content, QString* errStr = nullptr)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
    {
        if (errStr)
        {
            *errStr = file.errorString();
        }
        return false;
    }
    content = file.readAll();
    file.close();
    return true;
}
static bool readJson(const QByteArray& data, QJsonDocument& doc, QString* errStr = nullptr)
{
    QJsonParseError err;
    doc = QJsonDocument::fromJson(data, &err);
    if (doc.isNull())
    {
        if (errStr)
        {
            *errStr = err.errorString();
        }
        return false;
    }
    return true;
}
static bool readJson(const QByteArray& data, QJsonArray& array, QString* errStr = nullptr)
{
    QJsonDocument doc;
    bool ok = readJson(data, doc, errStr);
    if (ok)
    {
        array = doc.array();
    }
    return ok;
}
static bool readJson(const QByteArray& data, QJsonObject& object, QString* errStr = nullptr)
{
    QJsonDocument doc;
    bool ok = readJson(data, doc, errStr);
    if (ok)
    {
        object = doc.object();
    }
    return ok;
}
static bool readJsonFile(const QString& filePath, QJsonDocument& jsonDoc, QString* errStr = nullptr)
{
    QByteArray data;
    if (!readFile(filePath, data, errStr))
    {
        return false;
    }

    return readJson(data, jsonDoc, errStr);
}
static bool readJsonFile(const QString& filePath, QJsonObject& jsonObj, QString* errStr = nullptr)
{
    QByteArray data;
    if (!readFile(filePath, data, errStr))
    {
        return false;
    }
    if (readJson(data, jsonObj, errStr) == false)
    {
       
        // 使用QTextCodec将QByteArray从UTF-8转换为GBK
        QByteArray gbkArray = gb2312ToUtf8(data);

        int ret = readJson(gbkArray, jsonObj, errStr);
        return ret;
    }
    return true;
}
static bool readJsonFile(const QString& filePath, QJsonArray& jsonArray, QString* errStr = nullptr)
{
    QByteArray data;
    if (!readFile(filePath, data, errStr))
    {
        return false;
    }
    return readJson(data, jsonArray, errStr);
}
static bool writeFile(const QString& filePath, const QByteArray& content, QString* errStr = nullptr)
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly))
    {
        if (errStr)
        {
            *errStr = file.errorString();
        }
        return false;
    }
    QByteArray  contentResult;
    QTextCodec* codec = QTextCodec::codecForName("GB2312");
    if (codec) {
        // 将QString转换为ANSI编码的QByteArray
        contentResult = codec->fromUnicode(content);
        // 写入文件
      
    }
    else {
        // 处理错误，无法获取ANSI编码器
        contentResult = content;
    }


    file.write(contentResult);
    file.close();
    return true;
}
static bool writeJsonFile(const QString& filePath, const QJsonDocument& doc, QString* errStr = nullptr)
{
    return writeFile(filePath, doc.toJson(), errStr);
}
static bool writeJsonFile(const QString& filePath, const QJsonArray& jsonArray, QString* errStr = nullptr)
{
    return writeJsonFile(filePath, QJsonDocument(jsonArray), errStr);
}
static bool writeJsonFile(const QString& filePath, const QJsonObject& jsonObj, QString* errStr = nullptr)
{
    return writeJsonFile(filePath, QJsonDocument(jsonObj), errStr);
}

};