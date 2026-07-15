#pragma once

#include "generaltools_global.h"
#include <QString>

enum FileType {
    FileType_Project,
    FileType_Script,
    FileType_Track
};

namespace FileUtils
{
GENERALTOOLS_EXPORT void replaceLines(
    const QString &filePath,
    const QString &searchContent, const QString &replaceContent);

GENERALTOOLS_EXPORT QString getFilePathMd5(const QString &filePath);

GENERALTOOLS_EXPORT bool delFile(const QString &filePath);

GENERALTOOLS_EXPORT QString GetFileMD5(
    const FileType &fileType, const QString &filePathName);

GENERALTOOLS_EXPORT bool isFileExist(const QString &sFileName);

GENERALTOOLS_EXPORT bool isFolderExist(const QString &sFolderName);

GENERALTOOLS_EXPORT QString avaliableStorageDir();

GENERALTOOLS_EXPORT bool copyFileToFolder(const QString &sFileName,
                                          const QString &sDestFolderName,
                                          bool bCoverIfExist = true,
                                          bool isNeedMessageBoxIfFailed = false);
GENERALTOOLS_EXPORT bool copyFilesToFolder(const QString &sSrcFolderName,
                                          const QString &sDestFolderName,
                                          bool bCoverIfExist = true,
                                          int currentDepth = 0);
GENERALTOOLS_EXPORT bool copyFile(const QString &sFileName,
                                  const QString &sDestFileName,
                                  bool bCoverIfExist = true,
                                  bool isNeedMessageBoxIfFailed = false);

GENERALTOOLS_EXPORT bool deleteFile(const QString &sFileName);
GENERALTOOLS_EXPORT void delFiles(const QString &filePath);
GENERALTOOLS_EXPORT bool deleteFiles(const QStringList &fileList);

GENERALTOOLS_EXPORT QStringList getDirFileList(const QString &sDirPath);
GENERALTOOLS_EXPORT QStringList getFileList(const QString &sFolderName,
                                            const QStringList &sSuffix);
GENERALTOOLS_EXPORT QString getControllerFilePath(
    QString sFilePath, const QString &sPrefix);
GENERALTOOLS_EXPORT QStringList getControllerFileList(
    const QStringList &sFileList, const QString &sPrefix);

GENERALTOOLS_EXPORT QString getRealPath(const QString &path);

GENERALTOOLS_EXPORT QString reMappingToAbsoluteAndroidPath(const QString &srcPath);

GENERALTOOLS_EXPORT void copyFolderRecursively(const QString &srcFilePath, const QString &tgtFilePath, QStringList &makeFolderFileFaliedList, QStringList &copyFileFailedList);

GENERALTOOLS_EXPORT bool recursiveFolderForFileList(const QString &srcFilePath, QStringList &fileList);

GENERALTOOLS_EXPORT bool removeDirectoryRecursively(const QString &dirPath);

GENERALTOOLS_EXPORT QString getFileName(const QString &filePath);

GENERALTOOLS_EXPORT bool zipFolder(const QString &folderPath, const QString &zipSavePath);
}  // namespace FileUtils
