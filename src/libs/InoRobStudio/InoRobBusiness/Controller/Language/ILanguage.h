#pragma once
#include <string>
#include "dllspec.h"
#include <QObject>
#include "DataTypeDef.h"

using namespace std;

namespace InoRobBusiness
{

#pragma region 多国语言

// 语言项
typedef struct LanguageItem
{
    // 初始化
    void Initialize()
    {
        Code = "";
        Name = L"";
        IsFactory = false;
    }

    // 构造函数
    LanguageItem()
    {
        Initialize();
    }

    // 构造函数
    LanguageItem(const string &code, const wstring &name, bool isFactory)
    {
        Initialize();
        Code = code;
        Name = name;
        IsFactory = isFactory;
    }

    // 赋值运算符重载
    LanguageItem &operator=(const LanguageItem &other)
    {
        this->Code = other.Code;
        this->Name = other.Name;
        this->IsFactory = other.IsFactory;
        return (*this);
    }

    // 语言编码
    string Code;
    // 语言名称
    wstring Name;
    // 是否出厂支持
    bool IsFactory;

} LanguageItem;

// 语言持久化（对应 Language.json）
typedef struct Language
{
    // 初始化
    void Initialize()
    {
        Version = "";
        PackageVersion = "";
        IsInit = false;
        Current.Initialize();
        Items.clear();
    }

    // 构造函数
    Language()
    {
        Initialize();
    }

    // 赋值运算符重载
    Language &operator=(const Language &other)
    {
        this->Version = other.Version;
        this->PackageVersion = other.PackageVersion;
        this->IsInit = other.IsInit;
        this->Current = other.Current;
        this->Items.clear();
        this->Items.insert(other.Items.begin(), other.Items.end());
        return (*this);
    }

    // Language.json版本号（用于后续Language.json文件扩展）
    string Version;
    // 匹配的语言包版本号（上位机软件版本在发布时指定一个匹配的语言包版本）
    string PackageVersion;
    // 用户是否已初始化（选择）语言
    bool IsInit;
    // 当前语言
    LanguageItem Current;
    // 已安装的语言列表（键为语言编码）
    map<string, LanguageItem> Items;

} Language;

// 语言包（对应 ZH-CN.data 等语言包文件）
typedef struct LanguagePackage
{
    // 初始化
    void Initialize()
    {
        lang = "";
        name = L"";
        ver = "";
        date = "";
        entries.clear();
    }

    // 构造函数
    LanguagePackage()
    {
        Initialize();
    }

    // 语言编码
    string lang;
    // 语言名称
    wstring name;
    // 版本
    string ver;
    // 发布日期
    string date;
    // 词条
    map<wstring, wstring> entries;

} LanguagePackage;

#pragma endregion

// 语言包验证结果
enum LanguagePackageValidResult : int32s
{
    LANGUAGE_PACKAGE_VALID_SUCCESS = 0,          // 验证通过
    LANGUAGE_PACKAGE_VALID_FILE_ERROR = 1,       // 文件有误
    LANGUAGE_PACKAGE_VALID_CONT_ERROR = 2,       // 内容有误
    LANGUAGE_PACKAGE_VALID_VERSION_HIGH = 3,     // 版本不匹配 导入的版本高于当前版本
    LANGUAGE_PACKAGE_VALID_VERSION_LOW = 4,      // 版本不匹配 导入的版本低于当前版本
    LANGUAGE_PACKAGE_VALID_VERSION_UNKNOWN = 5,  // 版本不匹配 未知的版本 转doule失败
    LANGUAGE_PACKAGE_VALID_SIGN_FAILURE = 6,     // 签名验证失败
    LANGUAGE_PACKAGE_WRITE_SIGN_FAILURE = 7      // 签名写入失败
};
// 语言包初始化结果
struct LanguageInitState
{
    bool Init_Success;          // 初始化成功
    bool Package_Lack_Folder;   // 缺少语言文件夹
    bool Package_Lack_Json;     // 缺少JSON
    bool Json_Analy_Faild;      // JSON解析失败
    bool Package_Lack_Entry;    // 缺少词条包
    bool Package_Lack_Sign;     // 缺少sign
    bool Sign_Vaild_Failed;     // 语言包校验失败
    bool Entry_Analyse_Failed;  // 语言包解析失败
    void Init()
    {
        Init_Success = false;          // 初始化成功
        Package_Lack_Folder = false;   // 缺少语言或其子文件夹
        Package_Lack_Json = false;     // 缺少JSON
        Json_Analy_Faild = false;      // JSON解析失败
        Package_Lack_Entry = false;    // 缺少词条包
        Package_Lack_Sign = false;     // 缺少sign
        Sign_Vaild_Failed = false;     // 语言包校验失败
        Entry_Analyse_Failed = false;  // 语言包解析失败
    }
    void CopyFrom(LanguageInitState in)
    {
        Init_Success = in.Init_Success;                  // 初始化成功
        Package_Lack_Folder = in.Package_Lack_Folder;    // 缺少语言文件夹
        Package_Lack_Json = in.Package_Lack_Json;        // 缺少JSON
        Json_Analy_Faild = in.Json_Analy_Faild;          // JSON解析失败
        Package_Lack_Entry = in.Package_Lack_Entry;      // 缺少词条包
        Package_Lack_Sign = in.Package_Lack_Sign;        // 缺少sign
        Sign_Vaild_Failed = in.Sign_Vaild_Failed;        // 语言包校验失败
        Entry_Analyse_Failed = in.Entry_Analyse_Failed;  // 语言包解析失败
    }
};

class INOROBBUSINESS_CLASS ILanguage : public QObject
{
    Q_OBJECT
public:
    // 获取语言相关信息（Language.json）
    virtual void GetLanguage(Language &language) = 0;

    // 切换当前语言（注：需重启进程）
    virtual bool ChangeCurrentLanguage(const string &languageCode) = 0;

    // 设置控制器当前语言（中文：ZH-CN，英文：EN）
    virtual bool SetControllerLanguage(const string &languageCode) = 0;

    // 验证语言包（语言包在导入前需要进行验证）
    virtual LanguagePackageValidResult LanguagePackageValid(const string &filePath, string &languageCode, wstring &languageName) = 0;

    // 导入语言包
    virtual bool LanguagePackageImport(const string &filePath, const string &languageCode, const wstring &languageName) = 0;

    // 导入语言包到控制器
    virtual int importLanguagePackage2Controller(const string &filePath) = 0;

    // 根据词条键获取词条值（注：当键不存在时，返回false，无值）
    virtual bool GetEntry(const wstring &entryCode, wstring &returnEntryValue) = 0;

    // 根据词条键获取词条值（注：当键不存在时，把键当作值返回）
    virtual wstring GetEntrySimple(const wstring &entryCode) = 0;

    // 根据词条键获取词条值（注：当键不存在时，返回指定的默认值，以简化调用）
    virtual wstring GetEntrySetDefault(const wstring &entryCode, wstring returnDefaultValue = L"") = 0;

    // 全部还原至出厂设置（注：需重启进程）
    virtual bool RestoreToFactory() = 0;

    // 解析语言包（为插件等提供服务）
    virtual bool LanguagePackageParse(const string &entryFilePath, map<wstring, wstring> &entries) = 0;

    virtual void RequireLanguageInitState(LanguageInitState &in) = 0;

    // 单个语言包验证
    virtual LanguagePackageValidResult SingleLanguageFileValid(const string &langFilePath, const string &signFilePath, const bool writeJson) = 0;

    // 获取当前控制器语言包版本
    virtual int RequireLanguageVersionInController(string &version) = 0;

    // 强制更新当前控制器语言包缓存
    virtual int UpdataControllerMemoryCache(bool flag) = 0;

    // 同步语言包到本地
    virtual int synchronizeFromController() = 0;

    virtual bool isEnabled() = 0;
signals:
    void languageChanged(const string &languge);
};
}  // namespace InoRobBusiness
