#pragma once

#include <QObject>


namespace TR {
#define TEST QObject::tr("ON");
//const inline QString ABcdEF = QObject::tr("ABcdEF");
inline QString ON ()           { return    QObject::tr("ON"); }
inline QString OFF ()          { return    QObject::tr("OFF"); }
inline QString True ()         { return    QObject::tr("True"); }
inline QString False ()        { return    QObject::tr("False"); }

inline QString State ()        { return    QObject::tr("Status"); }
// inline QString Enable ()       { return    QObject::tr("Enable"); }
// inline QString Disenable ()    { return    QObject::tr("Disenable"); }
inline QString ConfigState ()  { return    QObject::tr("Status"); }
inline QString EditEnable ()   { return    QObject::tr("Enable edit"); }

inline QString Name ()         { return    QObject::tr("Name"); }
inline QString Type ()         { return    QObject::tr("Type"); }
inline QString Label ()        { return    QObject::tr("Label"); }
inline QString Range ()        { return    QObject::tr("Range"); }
inline QString Remark ()       { return    QObject::tr("Description"); }
inline QString Value ()        { return    QObject::tr("Value"); }
inline QString Switch ()       { return    QObject::tr("Switch"); }

inline QString ForceSwitch ()  { return    QObject::tr("Force switch"); }
inline QString Force ()        { return    QObject::tr("Force"); }
inline QString NoForce ()      { return    QObject::tr("NoForce"); }
inline QString Invalid ()      { return    QObject::tr("Invalid"); }

inline QString Current ()      { return    QObject::tr("Current"); }
inline QString Voltage ()      { return    QObject::tr("Voltage"); }
inline QString OpenPage ()     { return    QObject::tr("Open page"); }
inline QString Clicked ()      { return    QObject::tr("Clicked"); }

}


