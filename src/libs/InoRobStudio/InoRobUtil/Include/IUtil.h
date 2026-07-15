#pragma once

#include "dllspec.h"

namespace InoRobUtil
{
enum ERR_CODE
{
    OK = 0,
    // 参数为空
    ERR_PARAM_NULL,
    // 读取文件失败
    ERR_READ_FILE,
    // 写文件失败
    ERR_WRITE_FILE,
    // 未找到文件信息结束关键字
    ERR_NOT_FOUND_ENDFILEINFO,
    // 解析为JSON对象失败
    ERR_STR_TO_JSONOBJ,
    // JSON对象转为结构体数据失败
    ERR_JSONOBJ_TO_DATA,
    // 数据转换到JSON对象失败
    ERR_DATA_TO_JSONOBJ,
    // CRC校验错误
    ERR_FILE_CRC_CHECK,
    // FTP登录失败
    ERR_FTP_LOGIN,
    // FTP获取文件失败
    ERR_FTP_GETFILE,
    // FTP发送文件失败
    ERR_FTP_PUTFILE,
    // 业务版本不匹配
    ERR_VERSION_DISMATCH,
    // 文件格式不兼容
    ERR_CONTENT_DISMATCH,
    // 文件内容不匹配
    ERR_DATA_DISMATCH,
    // 文件信息有缺失
    ERR_FILEINFO_DEFECT,
    // 读取数据失败
    ERR_READDATA_FILE,
    // 触发异常
    ERR_TRY_CATCH,
    // 机型不匹配
    ERR_ROBOTTYPE_NOTMATCH,
};

/**
 * @brief ftp相关错误码
*/
enum class FtpErrCode : int
{
    // 成功
    OK = 0,
    // 文件路径为空
    PATH_NULL,
    // 目录路径为空
    DIR_NULL,
    // 改变目录失败
    CD_FAIL,
    // 连接失败
    CONNECT_FAIL,
    // 下载文件失败
    DOWNLOAD_FILE_FAIL,
    // 上传文件失败
    UPLOAD_FILE_FAIL,
    // 删除文件失败
    REMOVE_FILE_FAIL,
    // 重命名文件失败
    RENAME_FILE_FAIL,
    // 获取文件大小失败
    GET_FILE_SIZE_FAIL,
    // 创建目录失败
    CREATE_DIR_FAIL,
    // 删除目录失败
    REMOVE_DIR_FAIL,
    // 重命名目录失败
    RENAME_DIR_FAIL,
    // 获取目录大小失败
    GET_DIR_SIZE_FAIL,
    // 获取当前目录失败
    GET_CUR_DIR_FAIL,
    // 获取目录中的文件列表失败
    GET_FILE_LIST_FAIL,
    // 本地目录不存在
    LOCAL_DIR_NOT_EXISTED,
};

}  // namespace InoRobUtil