#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"

/*
    负载
    Create by WuJian at 2022/5/2
    Update by 周壮 at 2022/5 增加负载编辑相关
*/
namespace InoRobBusiness
{
#pragma region 枚举与结构体

enum LoadID
{
    LOAD_ID_LOAD_0 = 0,
    LOAD_ID_LOAD_1 = 1,
    LOAD_ID_LOAD_2 = 2,
    LOAD_ID_LOAD_3 = 3,
    LOAD_ID_LOAD_4 = 4,
    LOAD_ID_LOAD_5 = 5,
    LOAD_ID_LOAD_6 = 6,
    LOAD_ID_LOAD_7 = 7,
    LOAD_ID_LOAD_8 = 8,
    LOAD_ID_LOAD_9 = 9,
    LOAD_ID_LOAD_10 = 10,
    LOAD_ID_LOAD_11 = 11,
    LOAD_ID_LOAD_12 = 12,
    LOAD_ID_LOAD_13 = 13,
    LOAD_ID_LOAD_14 = 14,
    LOAD_ID_LOAD_15 = 15,
};

typedef struct _LOAD_ID_NAME_STRUCT_
{
    LoadID id;
    string name;
} LoadIDNameStruct;

#pragma endregion

class INOROBBUSINESS_CLASS ILoad : public QObject
{
    Q_OBJECT

public:
    virtual ~ILoad()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 通用

    // 初始化负载数据（由控制器初始化数据调用）
    virtual void InitData() = 0;

    // 获取负载号总数量
    virtual int16u GetCount() = 0;

#pragma endregion

    // 设定当前负载号
    virtual bool SetCurrentId(int16u currentId) = 0;

#pragma region 负载参数

    // 读取负载参数
    virtual bool GetLoadParam(int16u loadNo, LoadData &loadData) = 0;
    // 设置负载参数
    virtual bool SetLoadParam(int16u loadNo, LoadData loadData) = 0;

#pragma endregion

#pragma region 负载范围

    // 负载最小质量
    virtual double GetMinMass() = 0;
    // 负载最大质量
    virtual double GetMaxMass() = 0;
    // 负载最小质心
    virtual double GetMinCentroid() = 0;
    // 负载最大质心
    virtual double GetMaxCentroid() = 0;
    // 负载最小转动惯量
    virtual double GetMinInertia() = 0;
    // 负载最大转动惯量
    virtual double GetMaxInertia() = 0;
    // 检查当前负载参数
    virtual bool CheckCurLoadValid(LoadData data) = 0;
#pragma endregion

#pragma region 负载编辑相关

    // 保存
    virtual bool Save(int loadId, LoadData data, bool isSaveIDResult = false) = 0;
    // 刷新
    virtual bool Refresh(int loadId, LoadData &data) = 0;
    // 清零
    virtual bool Clear(int loadId) = 0;
    // load对应名称查询
    virtual string LoadIDNameSearch(LoadID loadId) = 0;
    // 操作权限
    virtual bool CheckAuthority() = 0;

    // 负载参数的控制权检查
    virtual bool checkLoadOperatePermission() = 0;

    // 读取负载用户数据
    virtual int refreshLoadUserData(LoadUserData &loadUserData) = 0;

    // 保存负载用户数据
    virtual bool saveLoadUserData(int16u loadNo, UserInstallParam &loadUserParam) = 0;

    // 检查LoadData
    virtual string checkloadDataValueValid(const LoadData &loadDataTemp) = 0;

Q_SIGNALS:
    // 负载数据改变事件
    void loadDataChanged(int8u data);

#pragma endregion
};
}  // namespace InoRobBusiness
