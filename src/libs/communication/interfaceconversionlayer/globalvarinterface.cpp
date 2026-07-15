#include "globalvarinterface.h"
#include "communication.h"
#include "IController.h"
#include "metatypeconversion.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "InoRobBusiness/Workstation/WorkstationDefault.h"

#include "cobotlogex.h"
#include "modulesutils.h"

//陆
/****************************************/
//调度
void GlobalVarInterface::setGlobalVarScheduler_B(bool flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarBScheduler(flag);
}

void GlobalVarInterface::setGlobalVarScheduler_R(bool flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarRScheduler(flag);
}

void GlobalVarInterface::setGlobalVarScheduler_D(bool flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarDScheduler(flag);
}

void GlobalVarInterface::setGlobalVarScheduler_PR(bool flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarPRScheduler(flag);
}

void GlobalVarInterface::setGlobalVarScheduler_String(bool flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarStringScheduler(flag);
}

//读
bool GlobalVarInterface::getGlobalVar_B_everyCol(QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarBDatas())
        return false;
    data.clear();
    data = MetaTypeConversion::tp2InoApi_globalVarBVariant(
        _IResource->getGlobalVarBDatas());
    return true;
}

bool GlobalVarInterface::getGlobalVar_R_everyCol(QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarRDatas())
        return false;
    data.clear();
    data = MetaTypeConversion::tp2InoApi_globalVarRVariant(
        _IResource->getGlobalVarRDatas());
    return true;
}
#if defined(INOCOBOTTP_MSVC_QT5)
bool GlobalVarInterface::getGlobalVar_B_everyCol(QList<QList<QVariant> > &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarBDatas())
        return false;
    data.clear();
    QVector<QVector<QVariant>> tempData =
        MetaTypeConversion::tp2InoApi_globalVarBVariant(
            _IResource->getGlobalVarBDatas());

    for (const QVector<QVariant>& innerVector : tempData) {
        QList<QVariant> innerList = innerVector.toList();  // 内层转换
        data.append(innerList);
    }
    return true;
}

bool GlobalVarInterface::getGlobalVar_R_everyCol(QList<QList<QVariant> > &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarRDatas())
        return false;
    data.clear();

    QVector<QVector<QVariant>> tempData = MetaTypeConversion::tp2InoApi_globalVarRVariant(
        _IResource->getGlobalVarRDatas());
    for (const QVector<QVariant>& innerVector : tempData) {
        QList<QVariant> innerList = innerVector.toList();  // 内层转换
        data.append(innerList);
    }
    return true;
}

bool GlobalVarInterface::getGlobalVar_D_everyCol(QList<QList<QVariant> > &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarDDatas())
        return false;
    data.clear();
    QVector<QVector<QVariant>> tempData = MetaTypeConversion::tp2InoApi_globalVarDVariant(
        _IResource->getGlobalVarDDatas());
    for (const QVector<QVariant>& innerVector : tempData) {
        QList<QVariant> innerList = innerVector.toList();  // 内层转换
        data.append(innerList);
    }
    return true;
}

bool GlobalVarInterface::getGlobalVar_String_everyCol(QList<QList<QVariant> > &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updateGlobalVarStringDatas())
        return false;
    std::array<std::string, GLOBAL_VAR_STRING_COUNT> source;
    source = _IResource->getGlobalVarStringDatas();

    QVector<QVector<QVariant>> tempData = MetaTypeConversion::tp2InoApi_globalVarStringVariant(source);
    for (const QVector<QVariant>& innerVector : tempData) {
        QList<QVariant> innerList = innerVector.toList();  // 内层转换
        data.append(innerList);
    }
    return true;
}

bool GlobalVarInterface::getGlobalVar_B_valuesCol(QList<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarBDatas())
        return false;
    std::array<unsigned char, GLOBAL_VAR_B_COUNT> source;
    source = _IResource->getGlobalVarBValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_R_valuesCol(QList<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarRDatas())
        return false;
    std::array<int, GLOBAL_VAR_R_COUNT> source;
    source = _IResource->getGlobalVarRValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_D_valuesCol(QList<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updataGlobalVarDDatas())
        return false;
    std::array<double, GLOBAL_VAR_D_COUNT> source;
    source = _IResource->getGlobalVarDValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_String_valuesCol(QList<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!_IResource->updateGlobalVarStringDatas())
        return false;
    std::array<std::string, GLOBAL_VAR_B_COUNT> source;
    source = _IResource->getGlobalVarStringDatas();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(QString::fromStdString(source[i])));
    return true;
}
#endif

bool GlobalVarInterface::getGlobalVar_D_everyCol(QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarDDatas())
        return false;
    data.clear();
    data = MetaTypeConversion::tp2InoApi_globalVarDVariant(
        _IResource->getGlobalVarDDatas());
    return true;
}

bool GlobalVarInterface::getGlobalVar_String_everyCol(QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updateGlobalVarStringDatas())
        return false;
    std::array<std::string, GLOBAL_VAR_STRING_COUNT> source;
    source = _IResource->getGlobalVarStringDatas();
    data = MetaTypeConversion::tp2InoApi_globalVarStringVariant(source);
    return true;
}

bool GlobalVarInterface::getGlobalVar_P_everyColForCurrentShow(int &currentRow, QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    //每页5个点 读前4页 当前页 加后5页 一共10页
    int currentPage = currentRow / 5;
    int startPage = currentPage - 4;
    int endPage = currentPage + 5;
    int pageNum = startPage - endPage + 1;
    if(startPage < 0)
        startPage = 0;
    if(endPage > GLOBAL_P_COUNT / 5)
        endPage = GLOBAL_P_COUNT / 5;
    pageNum = endPage - startPage + 1;
    std::vector<InoRobBusiness::GlobalPData> source(pageNum * 5);
    bool ret = _IResource->getGlobalPDatas(source, startPage, pageNum, false);
    if (!ret) {
        return false;
    }
    data = MetaTypeConversion::tp2InoApi_globalVarPVariant(source);
    return true;
}

bool GlobalVarInterface::getGlobalVar_JP_everyColForCurrentShow(int &currentRow, QVector<QVector<QVariant>> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    //每页5个点
    int currentPage = currentRow / 5;
    int startPage = currentPage - 4;
    int endPage = currentPage + 5;
    int pageNum = startPage - endPage + 1;
    if(startPage < 0)
        startPage = 0;
    if(endPage > GLOBAL_P_COUNT / 5)
        endPage = GLOBAL_P_COUNT / 5;
    pageNum = endPage - startPage + 1;
    std::vector<InoRobBusiness::GlobalJPData> source(pageNum * 5);
    bool ret = _IResource->getGlobalJPDatas(source, startPage, pageNum, false);
    if (!ret) {
        return false;
    }
    data = MetaTypeConversion::tp2InoApi_globalVarJPVariant(source);
    return true;
}

bool GlobalVarInterface::getGlobalVar_B_valuesCol(QVector<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarBDatas())
        return false;
    std::array<unsigned char, GLOBAL_VAR_B_COUNT> source;
    source = _IResource->getGlobalVarBValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_R_valuesCol(QVector<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarRDatas())
        return false;
    std::array<int, GLOBAL_VAR_R_COUNT> source;
    source = _IResource->getGlobalVarRValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_D_valuesCol(QVector<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updataGlobalVarDDatas())
        return false;
    std::array<double, GLOBAL_VAR_D_COUNT> source;
    source = _IResource->getGlobalVarDValues();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(source[i]));
    return true;
}

bool GlobalVarInterface::getGlobalVar_String_valuesCol(QVector<QVariant> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!_IResource->updateGlobalVarStringDatas())
        return false;
    std::array<std::string, GLOBAL_VAR_B_COUNT> source;
    source = _IResource->getGlobalVarStringDatas();
    int size = source.size();
    data.clear();
    for (int i = 0; i < size; ++i)
        data.push_back(QVariant(QString::fromStdString(source[i])));
    return true;
}

bool GlobalVarInterface::getGlobalVar_P_valuesCol(QVector<QVector<QVariant>> &data)
{
    // _IResource->updataGlobalVarPDatas();
    return true;
}

bool GlobalVarInterface::getGlobalVar_JP_valuesCol(QVector<QVector<QVariant>> &data)
{
    // _IResource->updataGlobalVarJPDatas();
    return true;
}

/****************************************/
//写
void GlobalVarInterface::ModifyItemLabel(InoLabelType type, int index, const QString &label)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::gs_Workstation.GetObj()->GetProject()->GetLabel()->ModifyItemLabel(LabelType(type), index, label.toStdString());
}

void GlobalVarInterface::ModifyItemDescription(InoLabelType type, int index, const QString &des)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::gs_Workstation.GetObj()->GetProject()->GetLabel()->ModifyItemLabel(LabelType(type), index, des.toStdString());
}

bool GlobalVarInterface::setGlobalVar_B_values(const int index, const unsigned char data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarBValue(data, index);
}

bool GlobalVarInterface::setGlobalVar_R_values(const int index, const int data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarRValue(data, index);
    // _IResource->setGlobalVarRFavorite(list[4].toBool(), row);
    // return true;
}

bool GlobalVarInterface::setGlobalVar_D_values(const int index, const double data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setGlobalVarDValue(data, index);
    // _IResource->setGlobalVarDFavorite(list[4].toBool(), row);
    return true;
}

bool GlobalVarInterface::setGlobalVar_String_values(const int index, const QString &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarStringValue(data.toStdString(), index);
}

bool GlobalVarInterface::setGlobalVar_B_favorite(const int index, const bool isFavorite)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarBFavorite(isFavorite, index);
}

bool GlobalVarInterface::setGlobalVar_R_favorite(const int index, const bool isFavorite)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarRFavorite(isFavorite, index);
}

bool GlobalVarInterface::setGlobalVar_D_favorite(const int index, const bool isFavorite)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->setGlobalVarDFavorite(isFavorite, index);
}
