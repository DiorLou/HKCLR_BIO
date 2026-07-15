#pragma once

#include "generaltools_global.h"
#include <QSize>

class QWidget;

namespace ResolutionUtils
{
GENERALTOOLS_EXPORT int getRatioWidth(const int &width);
GENERALTOOLS_EXPORT int getRatioHeight(const int &height);
GENERALTOOLS_EXPORT int getMinRatioSize(const int &size);
GENERALTOOLS_EXPORT QSize getRatioSize(const int &width, const int &height);
GENERALTOOLS_EXPORT QSize getRatioSize(const QSize &size);
GENERALTOOLS_EXPORT int getRatioFontWidth(
    const QString &content, int pixelSize = 16);
GENERALTOOLS_EXPORT void setRatioStyleSheet(QWidget *widget);
}  // namespace ResolutionUtils
