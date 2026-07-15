#pragma once
#include <string>
#include "DataTypeDef.h"
#include "IInoRobUtil.h"

using std::string;

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonObjOp
{
public:
    // 文件内容反序列化为cJSON对象
    static cJSON *FileToObj(const char *fileName);
    // cJSON对象序列化为文件
    static int ObjToFile(cJSON *pJson, const char *fileName);

    static int GetChildByInt8(cJSON *pJson, const char *pKeyStr, char &data);

    static int GetChildByInt16(cJSON *pJson, const char *pKeyStr, short &data);

    static int GetChildByInt32(cJSON *pJson, const char *pKeyStr, int &data);

    static int GetChildByUInt8(cJSON *pJson, const char *pKeyStr, unsigned char &data);

    static int GetChildByUInt16(cJSON *pJson, const char *pKeyStr, unsigned short &data);

    static int GetChildByUInt32(cJSON *pJson, const char *pKeyStr, unsigned int &data);

    static int GetChildByLong(cJSON *pJson, const char *pKeyStr, long &data);

    static int GetChildByLongLong(cJSON *pJson, const char *pKeyStr, LONGLONG &data);

    static int GetChildByFloat(cJSON *pJson, const char *pKeyStr, float &data);

    static int GetChildByDouble(cJSON *pJson, const char *pKeyStr, double &data);

    // static int GetChildByString(cJSON *pJson, const char *pKeyStr, CString &data);

    static int GetChildByString(cJSON *pJson, const char *pKeyStr, string &data);

    static int GetChildByBool(cJSON *pJson, const char *pKeyStr, bool &data);

    static int GetDouble(cJSON *pJson, double &data);

    static int GetFloat(cJSON *pJson, float &data);

    static int GetInt(cJSON *pJson, int &data);

    static int GetUShort(cJSON *pJson, unsigned short &data);

    static int GetShort(cJSON *pJson, short &data);

    static int GetBool(cJSON *pJson, bool &data);

    // 释放Json对象（使用完Json对象后务必调用）
    static void JsonDelete(cJSON *pJson);

#pragma region cJSON封装

    static cJSON *CjsonParse(const char *jsonStr);
    static char *CjsonPrint(cJSON *cJson);
    static char *CjsonPrintUnformatted(cJSON *cJson);
    static void CjsonMinify(char *json);
    static cJSON *CjsonDuplicate(cJSON *item, int recurse);

    static int CjsonGetArraySize(cJSON *array);
    static cJSON *CjsonGetArrayItem(cJSON *array, int item);
    static cJSON *CjsonGetObjectItem(cJSON *object, const char *string);

    static cJSON *CjsonCreateNull(void);
    static cJSON *CjsonCreateTrue(void);
    static cJSON *CjsonCreateFalse(void);
    static cJSON *CjsonCreateBool(int b);
    static cJSON *CjsonCreateNumber(double num);
    static cJSON *CjsonCreateString(const char *string);
    static cJSON *CjsonCreateArray(void);
    static cJSON *CjsonCreateObject(void);
    static cJSON *CjsonCreateIntArray(const int *numbers, int count);
    static cJSON *CjsonCreateFloatArray(const float *numbers, int count);
    static cJSON *CjsonCreateDoubleArray(const double *numbers, int count);
    static cJSON *CjsonCreateStringArray(const char **strings, int count);

    static void CjsonAddNumberToObject(cJSON *object, const char *string, int item);
    static void CjsonAddNumberToObject(cJSON *object, const char *string, float item);
    static void CjsonAddNumberToObject(cJSON *object, const char *string, double item);
    static void CjsonAddStringToObject(cJSON *object, const char *string, const char *item);
    static void CjsonAddBoolToObject(cJSON *object, const char *string, bool item);
    static void CjsonAddItemToObject(cJSON *object, const char *string, cJSON *item);
    static void CjsonAddItemToArray(cJSON *array, cJSON *item);

    static void CjsonInsertItemInArray(cJSON *array, int which, cJSON *newitem);
    static void CjsonReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
    static void CjsonReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);

    static cJSON *CjsonDetachItemFromArray(cJSON *array, int which);
    static void CjsonDeleteItemFromArray(cJSON *array, int which);
    static cJSON *CjsonDetachItemFromObject(cJSON *object, const char *string);
    static void CjsonDeleteItemFromObject(cJSON *object, const char *string);

#pragma endregion
};

}  // namespace InoRobUtil
