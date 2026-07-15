#pragma once

#include <QString>
#include "metatype_global.h"

class METATYPE_EXPORT ToolParam
{
public:
    ToolParam();
    ToolParam(const QString &toolName);
    ToolParam(const ToolParam &other);
    ToolParam &operator=(const ToolParam &other);
    bool operator==(const ToolParam &other) const;
    bool operator!=(const ToolParam &other) const;
    bool operator<(const ToolParam &other) const;

    void init();
    bool isExist() const;

    static void toolParamListSort(QList<ToolParam> &tar);
    static bool toolParamSort(
        const ToolParam first, const ToolParam second);

    QString m_toolName;

private:
    void copyOthertoSelf(const ToolParam &other);
};
