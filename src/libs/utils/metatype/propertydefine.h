#pragma once
#include <QString>
#include <QObject>
#include <QAbstractButton>

const char InfoFlow_Property[] = "InfornmationFlow";
const char InfoFlow_Split[] = " -> ";
const char InfoFlow_RbnIsWidgetIndex[] = "NoLogEnable";
const char InfoFlow_ToolBox[] = "InfoFlow_ToolBox";
const char InfoFlow_EditPassWord[] = "EditPassWord";

const char InfoFlow_HighLevelOperationLog[] = "InfoFlowHighLevelText";
const char InfoFlow_LowLevelOperationLog[] = "InfoFlowLowLevelText";

inline QString combineInfoFlow(QString secondInfoFLow, QString thirdInfoFlow)
{
    return secondInfoFLow + " -> " + thirdInfoFlow;
}


