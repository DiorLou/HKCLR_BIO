#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../GlobalDataTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 枚举与结构体

enum LoadID_V1
{
    LOAD_ID_LOAD_0_V1 = 0,
    LOAD_ID_LOAD_1_V1 = 1,
    LOAD_ID_LOAD_2_V1 = 2,
    LOAD_ID_LOAD_3_V1 = 3,
    LOAD_ID_LOAD_4_V1 = 4,
    LOAD_ID_LOAD_5_V1 = 5,
    LOAD_ID_LOAD_6_V1 = 6,
    LOAD_ID_LOAD_7_V1 = 7,
    LOAD_ID_LOAD_8_V1 = 8,
    LOAD_ID_LOAD_9_V1 = 9,
    LOAD_ID_LOAD_10_V1 = 10,
    LOAD_ID_LOAD_11_V1 = 11,
    LOAD_ID_LOAD_12_V1 = 12,
    LOAD_ID_LOAD_13_V1 = 13,
    LOAD_ID_LOAD_14_V1 = 14,
    LOAD_ID_LOAD_15_V1 = 15,
};

typedef struct _LOAD_ID_NAME_STRUCT_V1
{
    LoadID_V1 id;
    string name;
} LoadIDNameStruct_V1;

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Load_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static LoadID_V1 LoadID_ToProxy(LoadID loadID);
    static LoadID LoadID_FromProxy(LoadID_V1 loadID_V1);

    static bool LoadIDNameStruct_ToProxy(const LoadIDNameStruct &loadIDNameStruct, LoadIDNameStruct_V1 &loadIDNameStruct_V1);
    static bool LoadIDNameStruct_FromProxy(const LoadIDNameStruct_V1 &loadIDNameStruct_V1, LoadIDNameStruct &loadIDNameStruct);

#pragma endregion

#pragma region 构造与析构

private:
    ILoad *_load = nullptr;

public:
    Load_V1(ILoad *load);
    ~Load_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 初始化负载数据（由控制器初始化数据调用）
    void InitData();
    // 获取负载号总数量
    int16u GetCount();
    // 设定当前负载号
    bool SetCurrentId(int16u currentId);
    // 读取负载参数
    bool GetLoadParam(int16u loadNo, LoadData_V1 &loadData);
    // 设置负载参数
    bool SetLoadParam(int16u loadNo, LoadData_V1 loadData);
    // 负载最小质量
    double GetMinMass();
    // 负载最大质量
    double GetMaxMass();
    // 负载最小质心
    double GetMinCentroid();
    // 负载最大质心
    double GetMaxCentroid();
    // 负载最小转动惯量
    double GetMinInertia();
    // 负载最大转动惯量
    double GetMaxInertia();
    // 检查当前负载参数
    bool CheckCurLoadValid(LoadData_V1 data);
    // 保存
    bool Save(int loadId, LoadData_V1 data, bool isSaveIDResult = false);
    // 刷新
    bool Refresh(int loadId, LoadData_V1 &data);
    // 清零
    bool Clear(int loadId);
    // load对应名称查询
    string LoadIDNameSearch(LoadID_V1 loadId);
    // 操作权限
    bool CheckAuthority();
    // 负载参数的控制权检查
    bool checkLoadOperatePermission();
    // 读取负载用户数据
    int refreshLoadUserData(LoadUserData_V1 &loadUserData);
    // 保存负载用户数据
    bool saveLoadUserData(int16u loadNo, UserInstallParam_V1 &loadUserParam);
    // 检查LoadData
    string checkloadDataValueValid(const LoadData_V1 &loadDataTemp);
    // 负载数据改变事件
    rsignal<int8u> LoadDataChanged;

private:
    void LoadDataChangedHandler(int8u data);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
