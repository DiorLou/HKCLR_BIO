#pragma once
#include <vector>
#include <string>
#include "Include/IUtil.h"
#include "StringHelper.h"

using std::string;
using std::vector;

namespace InoRobUtil
{
// 获取当前工作路径
std::string INOROBUTIL_CLASS getCurrentWorkPath();
// 写入到文件
bool INOROBUTIL_CLASS WriteToFile(string filePath, vector<string> vecFile);
// 去除文件只读属性
bool INOROBUTIL_CLASS RemoveOnlyReadAttribut(const string &filePath);
// 添加换行符
void INOROBUTIL_CLASS AddNewLineCharacter(string &sLine);
// 判断文件是否存在
bool INOROBUTIL_CLASS FileExist(const string &filePath);
// 创建文件
bool INOROBUTIL_CLASS FileCreate(string filePath);
// 多层文件夹的创建
bool INOROBUTIL_CLASS MuliteDirectoryCreate(string folderPath);
// 文件夹是否存在
bool INOROBUTIL_CLASS DirectoryExist(string folderPath);
// 创建文件夹
bool INOROBUTIL_CLASS DirectoryCreate(string folderPath);
// 从文件中读取所有文本
bool INOROBUTIL_CLASS ReadAllTextFromFile(string filePath, string &content);
// 将文本内容覆盖写入文件
bool INOROBUTIL_CLASS WriteAllTextToFile(string filePath, string content);
// 将文本内容末尾添加写入文件
bool INOROBUTIL_CLASS AppendTextToFile(string filePath, string content);
// 获取当前路径文件夹，processName参数无效，统一返回exe执行路径
string INOROBUTIL_CLASS GetProcessDir(const string &processName = "");
// 删除文件
bool INOROBUTIL_CLASS FileDelete(const string &fileName);
// 删除文件夹
bool INOROBUTIL_CLASS DirectoryDelete(const string &folderPath);
// 清除文件夹内容
bool INOROBUTIL_CLASS DirectoryClear(const string &folderPath);

// 目录拷贝（递归拷贝目录中的所有内容，包括文件及子文件夹）
bool INOROBUTIL_CLASS DirectoryCopy(const string srcPath, const string destPath);

// 重命名文件
bool INOROBUTIL_CLASS FileRename(const string &srcFileName, const string &destFileName);
// 重命名文件夹
bool INOROBUTIL_CLASS DirectoryRename(const string &srcFolder, const string &destFolder);
// 拷贝文件
bool INOROBUTIL_CLASS FileCopy(const string &srcFile, const string &destFile, bool Forced = false);
// 移动文件
bool INOROBUTIL_CLASS FileMove(const string &srcFileName, const string &destFileName);
// 获取路径下的文件列表
void INOROBUTIL_CLASS GetFileList(std::vector<string> &files, const string &folder);
// 获取文件夹的内存大小（单位：字节）
uintmax_t INOROBUTIL_CLASS getFolderSize(const std::string &folder);

#pragma region 路径操作相关
// 按输入顺序整合路径
// 需要注意的是，如果存在根目录，如C:/..，必须作为第一个参数，否则将导致前面参数内容被忽略
string INOROBUTIL_CLASS CombinePath(string path0, string path1);
string INOROBUTIL_CLASS CombinePath(string path0, string path1, string path2);
// 将路径的分隔符转换为系统偏好的分隔符，例如，在 Windows 上 \ 是偏好分隔符， foo/bar 将被转换为 foo\bar
string INOROBUTIL_CLASS GetPreferredPath(string path);
// 返回路径的根名，如C:/a/b，返回C:/
string INOROBUTIL_CLASS GetRootDirectory(string path);
// 返回相对根目录，如C:/a/b，返回a/b
string INOROBUTIL_CLASS GetRelativeDirectory(string path);
// 返回路径的全目录，如C:/a/b/c.txt，返回C:/a/b
string INOROBUTIL_CLASS GetDirectory(string path);
string INOROBUTIL_CLASS RemovePathPrefix(const string &full_path, const string &prefix_to_remove);

// 返回文件名称，带后缀
string INOROBUTIL_CLASS GetFileName(string path);
// 返回文件名称，不带后缀
string INOROBUTIL_CLASS GetFileNameWithoutExtension(string path);
// 返回文件后缀
string INOROBUTIL_CLASS GetExtension(string path);
// 返回文件MD5
string INOROBUTIL_CLASS GetLocalFileMd5(string path);
// 路径是否有根名
bool INOROBUTIL_CLASS HasRootDirectory(string path);
// 路径是否有文件名，如C:/a/b，文件名为b，则返回true，如C:/a/b/，这样为无文件名，返回false
bool INOROBUTIL_CLASS HasFileName(string path);
// 路径是否有后缀
bool INOROBUTIL_CLASS HasExtension(string path);

// 读取UTF8-BOM编码的文本文件
bool INOROBUTIL_CLASS ReadUtf8BomFile(const string &filePath, string &fileContent);
// 写入UTF8-BOM编码的文本文件
bool INOROBUTIL_CLASS WriteUtf8BomFile(const string &filePath, const string &fileContent);

// 解析模式字符串以获取文件名
bool INOROBUTIL_CLASS FindFirstMatchFile(const std::string &pattern, std::string &name);

// .zip文件解压
int INOROBUTIL_CLASS UnZip(const char *zipFile, const char *outputDir, const std::string &password = "");

// 获取指定路径下的第一个文件夹名称
std::string INOROBUTIL_CLASS getFirstDirectory(const std::string &path);

// 解密文件
int INOROBUTIL_CLASS decryptFile(const string &srcFile, string strKey = "Inovance");

#pragma endregion

}  // namespace InoRobUtil
