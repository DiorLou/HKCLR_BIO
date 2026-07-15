#pragma once
#include "metatype_global.h"
class QString;

class METATYPE_EXPORT Ori
{
public:
    Ori();
    Ori(double w, double x, double y, double z);
    Ori(double rx, double ry, double rz);
    Ori(const Ori &other);
    Ori operator = (const Ori &other);
    bool operator == (const Ori &other) const;
    bool operator != (const Ori &other) const;

    void init();

    static QString ori2StringForScriptInterface(const Ori &src);
    static QString ori2String(const Ori &src);

    static QString ori2String_Euler(const Ori &src);
    static Ori string2Ori_Euler(const QString &src);

    double m_w; /**< W = cos (0.5 × a),  angle a*/
    double m_x; /**< x = X × sin (0.5 × a), axis (X Y Z) and angle a*/
    double m_y; /**< y = Y × sin (0.5 × a), axis (X Y Z) and angle a */
    double m_z; /**< z = Z × sin (0.5 × a), axis (X Y Z) and angle a */

    double m_rx;  //unit : degree
    double m_ry;
    double m_rz;

private:
    void copyOthertoSelf(const Ori &other);
};
