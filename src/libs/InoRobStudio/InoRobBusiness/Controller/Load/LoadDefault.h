#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS LoadDefault : public ILoad
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService;
    // 连接
    IConnection *m_Connection;
    // 监控
    IMonitor *m_Monitor;

public:
    LoadDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~LoadDefault();
    void init() override;
#pragma endregion

#pragma region 通用

    // 初始化负载范围
    void InitData();
    int16u GetCount();

#pragma endregion

    bool SetCurrentId(int16u currentId);

#pragma region 负载参数

    bool GetLoadParam(int16u loadNo, LoadData &loadData);
    bool SetLoadParam(int16u loadNo, LoadData loadData);

#pragma endregion

#pragma region 负载范围

    double GetMinMass();
    double GetMaxMass();
    double GetMinCentroid();
    double GetMaxCentroid();
    double GetMinInertia();
    double GetMaxInertia();

#pragma endregion

#pragma region 负载编辑相关

    bool Save(int loadId, LoadData data, bool isSaveIDResult = false);
    bool Refresh(int loadId, LoadData &data);
    bool Clear(int loadId);
    // loadId对应名称查询
    string LoadIDNameSearch(LoadID loadId);
    // 操作权限
    bool CheckAuthority();
    // 检查当前负载参数
    bool CheckCurLoadValid(LoadData data);

    // 负载参数的控制权检查
    bool checkLoadOperatePermission();

    // 读取负载用户数据
    int refreshLoadUserData(LoadUserData &loadUserData);

    // 保存负载用户数据
    bool saveLoadUserData(int16u loadNo, UserInstallParam &loadUserParam);

    string checkloadDataValueValid(const LoadData &loadDataTemp);
#pragma endregion
private:
    // 从控制器获取负载用户数据文件
    bool getLoadUserDataFile();

    // 从文件中获取负载用户数据
    bool readLoadUserDataFromFile();

    // 放置负载用户数据文件到控制器
    bool putLoadUserDataFile();

    // 写负载用户数据到文件
    bool writeLoadUserDataToFile();

    // 负载范围限制（连接时读取）
    int ReadLoadRange(double &minMass, double &maxMass, double &minCogPos, double &maxCogPos, double &minInertia, double &maxInertia);

private:
    // 检查参数是否合法
    bool CheckLoadParaValid(LoadData theLoad);

    // 负载最小质量
    double m_MinMass;
    // 负载最大质量
    double m_MaxMass;
    // 负载最小质心
    double m_MinCentroid;
    // 负载最大质心
    double m_MaxCentroid;
    // 负载最小转动惯量
    double m_MinInertia;
    // 负载最大转动惯量
    double m_MaxInertia;

    // 所有负载用户数据
    LoadUserData *_loadUserData;

    // 机械单元类型轴数数组
    static const LoadIDNameStruct _loadIDNameArray[16];

    static const std::string _localUserFilePath;

    static const std::string _remoteUserFilePath;

    static const std::string _userFileName;

    static const std::string _tmpUserFileName;
};

}  // namespace InoRobBusiness
