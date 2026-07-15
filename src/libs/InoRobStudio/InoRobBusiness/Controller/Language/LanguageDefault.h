#pragma once
#include <string>
#include "IInoRobBusiness.h"

using namespace std;

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS LanguageDefault : public ILanguage
{
#pragma region 构造 /析构/公共

private:
    IDataSrvBase *_pDataSrv = nullptr;
    void Init();

public:
    static LanguageDefault *instance()
    {
        static LanguageDefault instance;
        return &instance;
    }

    void setDependencies(IConnection *pCon, IDataSrvBase *pDataSrv);

    // 词条转义与还原
    void EntryEscape(wstring &content);
    void EntryRestore(wstring &content);

    // 用于存储遇到的未知转义字符串
    string unkownTranlsteSign;
#pragma endregion

#pragma region 内存与持久化

public:
    // 语言内存对象
    Language *m_Language;
    // 语言包（词条）内存对象
    LanguagePackage *m_LanguagePackage;

public:
    // 将当前语言对应的词条文件解析至内存对象
    bool LoadLanguagePackage();

    // 查找最后一个子串
    size_t FindLastStrs(const string &in, const string &subStr);

    // 语言初始化状态结构体
    LanguageInitState m_languageInitState;

    // 将词条文件片段解析至指定对象（注：该方法通常会被连续调用，调用前请正确初始化languagePackage对象）
    bool LoadLanguagePackageSegment(const string &inputText, map<wstring, wstring> &entries);
#pragma endregion

#pragma region 实现接口

public:
    // 获取语言相关信息
    void GetLanguage(Language &language);

    // 切换当前语言
    bool ChangeCurrentLanguage(const string &languageCode);

    // 设置控制器语言当前语言
    bool SetControllerLanguage(const string &languageCode);

    // 验证语言包（语言包在导入前需要进行验证）
    LanguagePackageValidResult LanguagePackageValid(const string &filePath, string &languageCode, wstring &languageName);

    // 导入语言包（语言包在导入前必须通过验证）
    bool LanguagePackageImport(const string &filePath, const string &languageCode, const wstring &languageName);

    int importLanguagePackage2Controller(const string &filePath) override;

    // 根据词条键获取词条值（注：当键不存在时，返回false，无值）
    bool GetEntry(const wstring &entryCode, wstring &returnEntryValue);

    // 根据词条键获取词条值（注：当键不存在时，把键当作值返回）
    wstring GetEntrySimple(const wstring &entryCode);

    // 根据词条键获取词条值（注：当键不存在时，返回指定的默认值，以简化调用）
    wstring GetEntrySetDefault(const wstring &entryCode, wstring returnDefaultValue = L"");

    // 全部还原至出厂设置
    bool RestoreToFactory();

    // 语言模块初始化状态
    void RequireLanguageInitState(LanguageInitState &in);

    // 解析语言包（为插件等提供服务）
    bool LanguagePackageParse(const string &entryFilePath, map<wstring, wstring> &entries);

    // 验证单个语言包 控制器 PC TP 控制器
    LanguagePackageValidResult SingleLanguageFileValid(const string &langFilePath, const string &signFilePath, const bool writeJson);

    // 获取当前控制器语言包版本
    int RequireLanguageVersionInController(string &version);

    // 强制更新当前控制器语言包缓存
    int UpdataControllerMemoryCache(bool flag);

    // 提取语言包版本号，V4R24C2-->4242
    int GetPackageversionNum(const string &cStrVersion);

    // 从控制器同步语言包
    int synchronizeFromController() override;

    bool isEnabled() override;

#pragma endregion

private:
    LanguageDefault();
    virtual ~LanguageDefault();
    LanguageDefault(const LanguageDefault &other) = delete;
    const LanguageDefault &operator=(const LanguageDefault &other) = delete;

    // ftp从控制器获取语言包
    int ftpGetLanguageFile(ftp::client &ftp, string path, std::string fthToPath, std::string curDirName);
    int ftpSendLanguageFile(std::string localPathe);

    bool _isEnabled = false;
    std::string _rootDir;
    IConnection *_pConnection = nullptr;
};
}  // namespace InoRobBusiness
