#pragma once

class QString;
#include "metatype_global.h"
class METATYPE_EXPORT Pos
{
public:
    Pos();
    Pos(const double &x, const double &y, const double &z);
    Pos(const Pos & other);
    Pos operator= (const Pos &other);
    bool operator== (const Pos &other) const;
    bool operator!= (const Pos &other) const;

    Pos operator+ (const Pos & p) const;
    Pos operator- (const Pos & p) const;

    static QString pos2StringForScriptInterface(const Pos &src);
    static QString pos2String(const Pos &src);

    void init();

    double m_x;  //Unit: millimeter
    double m_y;
    double m_z;

private:
    void copyOthertoSelf(const Pos &other);
};
