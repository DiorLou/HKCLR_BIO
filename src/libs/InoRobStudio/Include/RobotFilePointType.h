// 机器人程序文件内P点类型定义

#ifndef ROBOTFILEPOINTTYPE
#define ROBOTFILEPOINTTYPE
#include <string>
#include <vector>
using std::string;
using std::vector;

class CRobotFilePointType
{
public:
    CRobotFilePointType operator=(const CRobotFilePointType &other)
    {
        if (this == &other)
        {
            return *this;
        }

        // 赋值
        sName = other.sName;

        vPos.clear();
        for (vector<double>::const_iterator it = other.vPos.begin(); it != other.vPos.end(); it++)
        {
            vPos.push_back(*it);
        }

        for (int i = 0; i < 4; i++)
        {
            nQ[i] = other.nQ[i];
        }

        nCoorType = other.nCoorType;
        nToolSN = other.nToolSN;
        nUserSN = other.nUserSN;

        return *this;
    }

public:
    // 数据成员
    string sName;         // 坐标点名称，如P001
    vector<double> vPos;  // 坐标点
    int nQ[4];            // 杆间参数
    int nCoorType;        // 坐标系类型
    int nToolSN;          // 工具号
    int nUserSN;          // 用户号
};

#endif