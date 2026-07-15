/**
 * @copyright 深圳汇川技术股份有限公司 版权所有(C) All rights reserved
 * @file func_activate_mamager.h
 * @brief 功能激活管理功能模块
 * @details 负责软件功能授权激活的管理，主要基于用户需求激活功能与激活文件授权功能的同步
 * @author chenhaokun
 * @date 2022-07-08
 * @version V1.0
 * @note
 */

#ifndef __FUNC_ACTIVATE_MAMAGER_H_
#define __FUNC_ACTIVATE_MAMAGER_H_

/** @brief 对于 C++ 程序调用 C 库，相应的接口应该采用 C 语言的修饰符 */
#ifdef __cplusplus
    #define FORCE_C_BEGIN \
        extern "C"        \
        {
    #define FORCE_C_END }
#else
    #define FORCE_C_BEGIN
    #define FORCE_C_END
#endif

#define INET_API __declspec(dllimport)

FORCE_C_BEGIN
/**@enum FuncActivateErr
 *  @brief 功能激活错误码
 */
typedef enum FuncActivateErr
{
    ACTIVATE_SUCC,          /**< 功能激活成功 */
    ACTIVATE_FAIL,          /**< 功能激活失败 */
    ACTIVATE_ERROR_FILE,    /**< 功能激活文件有误 */
    ACTIVATE_ERROR_DEVICE,  /**< 功能激活设备有误 */
    ACTIVATE_ERROR_FUNC,    /**< 功能激活功能有误 */
    ACTIVATE_ERROR_REPEAT,  /**< 功能重复激活 */
    ACTIVATE_ERROR_UNKNOWN, /**< 功能激活功能未定义错误 */
} enFuncActivateErr;

/**@struct FuncConfig
 *  @brief 用户功能配置数据
 */
typedef struct FuncConfig
{
    // 待激活功能配置数据功能掩码
    unsigned char func_mask[32];
    // 待激活功能配置数据功能掩码长度
    unsigned int func_mask_len;
    // 待激活产品到 SN  码
    char szSNCode[64];
} stFuncConfig;

/**
 * @brief   获取设备端加密芯片参数接口
 * @pre     上位机和 arm 设备建立正常通信连接
 * @param romid    存放获取的 8 字节加密芯片 romid 信息地址/缓存
 * @param userdata 存放获取的 32 字节加密芯片用户数据信息地址/缓存
 * @param etag     存放获取的 32 字节加密芯片电子标签数据信息地址/缓存
 **/
typedef int (*pf_get_chip_param)(unsigned char *romid, unsigned char *userdata, unsigned char *etag);

/**
 * @brief   设置设备端加密芯片参数接口
 * @pre     上位机和 arm 设备建立正常通信连接
 * @param userdata 上位机程序下发到 arm 设备端的加密芯片用户数据
 * @param secret 上位机程序下发到 arm 设备端的加密芯片密钥数据
 * @note    特殊说明，如函数是否可重入，函数属于同步还是异步（可选）
 **/
typedef int (*pf_update_chip_config)(unsigned char *userdata, unsigned char *secret);

/**@struct FuncProtocol
 *  @brief 依赖外部实现的上位机与 arm 设备进行数据交互的协议功能函数
 */
typedef struct FuncProtocol
{
    pf_get_chip_param get_chip_param;
    pf_update_chip_config update_chip_config;
} stFuncProtocol;

/**
 * @brief   注册协议功能函数
 * @param   func_list 存放协议功能函数的结构体
 * @details 需要提供获取/写入设备端加密芯片参数信息的协议功能函数详细接口见 @ref stFuncProtocol
 * @pre     上位机程序与 arm 设备端能够建立正常通信，且可以通过注册的协议功能函数进行数据交互
 * @note    在调用该模块的其他函数前必须先调用该函数
 * @return  void 无返回值
 **/
INET_API void regist_protocol_func(stFuncProtocol func_list);

/**
 * @brief 获取加密设备内部用户数据
 *
 * @param buf_userdata 用户数据存放缓存/指针
 * @return int 获取到有效用户数据返回大小
 * @retval -1 失败
 */
INET_API int get_userdata(char *buf_userdata);

/**
 * @brief 创建激活配置文件
 *
 * @param file_name 配置文件名
 * @param func 配置文件中的目标激活功能配置
 * @return int 创建结果
 * @retval 0 成功
 */
INET_API int export_activate_config(char *file_name, stFuncConfig *func);

/**
 * @brief 导入激活文件激活功能
 *
 * @param file_name 激活文件名
 * @return enFuncActivateErr 激活结果
 */
INET_API enFuncActivateErr import_activate_file(char *file_name);

FORCE_C_END

#endif  // end of __FUNC_ACTIVATE_MAMAGER_H_
