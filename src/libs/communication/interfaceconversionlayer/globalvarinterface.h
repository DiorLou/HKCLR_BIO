#pragma once

#include <QVector>
#include "communication_global.h"
#include "labeldata.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
struct GlobalVarBData;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT GlobalVarInterface
{
public:
    GlobalVarInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    //调度  不使用 避免模型层轮询耗时
    void setGlobalVarScheduler_B(bool flag);
    void setGlobalVarScheduler_R(bool flag);
    void setGlobalVarScheduler_D(bool flag);
    void setGlobalVarScheduler_PR(bool flag);
    void setGlobalVarScheduler_String(bool flag);
    //读
    bool getGlobalVar_B_everyCol(QVector<QVector<QVariant>> &);
    bool getGlobalVar_R_everyCol(QVector<QVector<QVariant>> &);
    bool getGlobalVar_D_everyCol(QVector<QVector<QVariant>> &);
    bool getGlobalVar_String_everyCol(QVector<QVector<QVariant>> &);
    bool getGlobalVar_P_everyColForCurrentShow(int &currentRow, QVector<QVector<QVariant>> &);
    bool getGlobalVar_JP_everyColForCurrentShow(int &currentRow, QVector<QVector<QVariant>> &);
#if defined(INOCOBOTTP_MSVC_QT5)
    bool getGlobalVar_B_everyCol(QList<QList<QVariant>> &);
    bool getGlobalVar_R_everyCol(QList<QList<QVariant>> &);
    bool getGlobalVar_D_everyCol(QList<QList<QVariant>> &);
    bool getGlobalVar_String_everyCol(QList<QList<QVariant>> &);

    bool getGlobalVar_B_valuesCol(QList<QVariant> &data);
    bool getGlobalVar_R_valuesCol(QList<QVariant> &data);
    bool getGlobalVar_D_valuesCol(QList<QVariant> &data);
    bool getGlobalVar_String_valuesCol(QList<QVariant> &data);
#endif

    //只读值 没啥用
    bool getGlobalVar_B_valuesCol(QVector<QVariant> &data);
    bool getGlobalVar_R_valuesCol(QVector<QVariant> &data);
    bool getGlobalVar_D_valuesCol(QVector<QVariant> &data);
    bool getGlobalVar_String_valuesCol(QVector<QVariant> &data);
    bool getGlobalVar_P_valuesCol(QVector<QVector<QVariant>> &data);
    bool getGlobalVar_JP_valuesCol(QVector<QVector<QVariant>> &data);

    //写
    bool setGlobalVar_B_values(const int index, const unsigned char data);
    bool setGlobalVar_R_values(const int index, const int data);
    bool setGlobalVar_D_values(const int index, const double data);
    bool setGlobalVar_String_values(const int index, const QString &data);
    bool setGlobalVar_B_favorite(const int index, const bool isFavorite);
    bool setGlobalVar_R_favorite(const int index, const bool isFavorite);
    bool setGlobalVar_D_favorite(const int index, const bool isFavorite);
    //修改标签 描述
    void ModifyItemLabel(InoLabelType type, int index, const QString &label);
    void ModifyItemDescription(InoLabelType type, int index, const QString &des);
};
