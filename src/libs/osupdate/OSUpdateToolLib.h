#pragma once
#include "osupdate_global.h"

#define OS_UPDATE_TOOL_LIB_VERSION "V1R1C0B2"

#include <string>

#define OS_UPDATE_TOOL_DEMO_VERSION "V1R1C0B2"

enum UPDateChannel
{
    USB_TTY = 0,
    SD,
    NET,
    USB_IMG,
    SD_BOOT,
    SD_FORMAT,
};
/*
* A40i各种模式定义：
    BSP_UPDATE,//使用bsp.zip进行升级，不进行product.zip升级,可USB tty\NET,
    BSP_INSTALL,//使用bsp.zip进行升级，不进行product.zip升级,可USB tty\NET,
    PRODUCT_UPDATE,//使用product.zip进行升级，不进行bsp.zip升级,可USB tty\NET,
    PRODUCT_INSTALL,//使用product.zip进行升级，不进行img升级，可USB tty\NET,
    SYS_UPDATE ,//使用bsp.zip进行升级，使用product.zip升级，可USB tty\NET,
    SYS_INSTALL,//使用img/bsp.zip进行升级,img烧录完成后，传入product.zip升级，SD，usb uboot,NET,USB tty,
*/
enum UPDateMode
{
    NORMAL = 0,
    BSP_UPDATE,
    BSP_INSTALL,
    PRODUCT_UPDATE,
    PRODUCT_INSTALL,
    SYS_UPDATE,
    SYS_INSTALL,
    FACTORY_INSTALL_START,
    FACTORY_INSTALL_STOP,
    FILE_SEND,
	RUN_DIRECTLY,
};

enum E_SendFileStatus//文件传输状态
{
    StatusEstablish = 0,//文件传输初始状态
    StatusTransmit,//文件传输中
    StatusFinish,//文件传输结束
    StatusShRunning,//脚本执行中
    StatusUpdateSuccess,//升级或刷机成功
    StatusAbort,//传输中断
    StatusTimeout,//升级超时
    StatusError,//升级错误
    StatusWaitBurnDevice,//等待USB设备插入
    StatusBurnImging,//镜像烧录中
    //CARD数值由第三方库决定，不能修改
    CARD_OK = 10,					//烧写完成
    CARD_PROGRESS = 20,			//烧写进度
    CARD_STEP = 30,				//烧写步骤
    CARD_INFO = 40,				//烧写信息
    CARD_WARN = 50,				//警告信息
    CARD_ERROR = 60,			//烧写出错
    StatusBurnImgFinish,//镜像烧录完成
    StatusBurnImgErr,//镜像烧录错误

};

enum E_ERR_CODE//错误码
{
    ERR_OK = 0,
    ALREADYLOGIN,//用户已登录（暂未用到）
    ERR_BURNIMG_INIT_FAIL,//烧录初始化失败
    ERR_BURNIMG_TIMEOUT,//烧录镜像超时
    ERR_SENDFILE_TIMEOUT,//发送文件超时
    ERR_SENDFILE_ABORT,//发送文件中断
    ERR_WAITCMD_TIMEOUT,//等待命令响应超时
    ERR_MEM,//内存申请失败
    ERR_RUNNING,//上次升级未完成
    ERR_UNZIP,//解压失败
    ERR_DIR,//文件目录异常
    ERR_NO_DEVICES_FOUND,//找不到设备
    ERR_BURNIMG_FAIL,//IMG烧录失败
};
enum E_DEVICE
{
    E_A40I,
    E_T113,
    E_RK3568,
};
struct OSUpdateToolStatus {
    int status;
    int progress; // 进度  
    int errorCode; // 错误码  
    std::string errorString; // 错误字符串  
};
struct NetCfg {
    char hostname[32];
    char username[32];
    char password[32];
};
struct UsbTtyCfg {
    char username[32];
    char password[32];
};
struct UpdateCfg {
    std::string Src; // 源地址
    std::string Dest;//目标地址
    std::string WorkDir;//解压地址
    int update_mode;
    int cmd_code;
    E_DEVICE device;
    NetCfg netcfg;
    UsbTtyCfg usbttycfg;
    bool EraseFlag;
    bool BSPForceUpdate;
};
struct OSUpdateToolLibCfg {
    std::string Logpath;
    bool LogEnable;
};

class OSUPDATE_EXPORT OSUpdateToolLib
{
public:
    // 构造函数  
    OSUpdateToolLib(OSUpdateToolLibCfg *Libcfg = NULL);
    // 析构函数  
    ~OSUpdateToolLib();
    // 成员函数  
    int Update(UpdateCfg cfg);
    int SSHDebugCmd(UpdateCfg cfg, std::string cmd, char* result, int size);
    OSUpdateToolStatus GetStatus();
private:
    int A40iUpdate(UpdateCfg cfg);
    //预处理固件
    int PreFirmware(UpdateCfg cfg);
    int SetUpdateMode(const char* dir, int size);
    int WaitSendFile(int timeout);
    int WaitSSHCmdSuccess(UpdateCfg cfg, std::string cmd, std::string WaitString, int timeout);
    void CleanStatus();

    UpdateCfg m_cfg;
    OSUpdateToolLibCfg m_Libcfg;
    OSUpdateToolStatus m_status;
};

