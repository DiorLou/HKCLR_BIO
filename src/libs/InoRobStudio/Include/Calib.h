// CalibCe.h : CalibCe DLL 的主头文件

#ifdef CALIBDLL_EXPORTS
    #define CALIBDLL_API __declspec(dllexport)
#else
    #define CALIBDLL_API __declspec(dllimport)
#endif

// 如果改变 N_PT 的定义，库需要重新编译。请不要改变
#define N_PT 9  // 标定输入点的个数：至少4个

#ifndef DEF_VISION_ERR_PARAM
    #define DEF_VISION_ERR_PARAM
typedef struct
{
    double XavgError;    // x方向平均误差
    double YavgError;    // y方向平均误差
    double XmaxError;    // x方向最大误差
    double YmaxError;    // y方向最大误差
    double XmmPerPixel;  // x方向单位像素的尺寸
    double YmmPerPixel;  // y方向单位像素的尺寸
    double ToolOffsetX;  // x方向工具偏移
    double ToolOffsetY;  // y方向工具偏移
} VISION_ERR_PARAM;
#endif

/*************************************************
  函数名:	// EyeToHandCalib()
  描述:		// 求n对像素坐标与机器人坐标关系的映射

  输入:		// （1）rtInputPt：				N_PT个机器人位置的x，y坐标
            // （2）imageInputPt：			N_PT个像素位置的u，v坐标
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；请检查有无重合点
*************************************************/
CALIBDLL_API int EyeToHandCalib(double rtInputPt[N_PT][2], double imageInputPt[N_PT][2], double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);
/*************************************************
  函数名:	// EyeToHandCalibN()
  描述:		// 求n对像素坐标与机器人坐标关系的映射

  输入:		// （1）n：					n对机器人和像素坐标（限制：4<=n<=100）
            // （2）rtInputPt			法兰盘中心对应的机器人坐标值（无工具）
            // （3）tcPt				两点求工具参数
            // （4）imageInputPt：		对应的像素坐标值
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；请检查有无重合点
                       2；n超范围
                       3；工具两点重合
*************************************************/
CALIBDLL_API int EyeToHandCalibN(int n, double rtInputPt[][8], double tcPt[2][8], double imageInputPt[][2], double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);
/*************************************************
  函数名:	// EyeToHandCalibN2()
  描述:		// 求n对像素坐标与机器人坐标关系的映射

  输入:		// （1）n：					n对机器人和像素坐标（限制：4<=n<=100）
            // （2）rtInputPt			法兰盘中心对应的机器人坐标值（无工具）（基坐标系）
            // （3）tcPt				两点求工具参数（基坐标系）
            // （4）imageInputPt：		对应的像素坐标值
            // （5）usrParam			标定平面（即工作平面）所在的用户坐标系
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；请检查有无重合点
                       2；n超范围
                       3；工具两点重合
*************************************************/
CALIBDLL_API int EyeToHandCalibN2(int n, double rtInputPt[][8], double tcPt[3][8], double imageInputPt[][2], double usrParam[6],
                                  double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);

/*************************************************
  函数名:	// EyeOnHandCalib()
  描述:		// 像素坐标与机器人坐标关系的映射
  功能:		// 求标定参数：3*3

  输入:		// （1）fixedPt：				机器人尖端的一个示教点
            // （2）rtInputPt：				相机所在关节的机器人坐标值
            // （3）imageInputPt：			对应的像素坐标值
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；请检查有无重合点
//注意事项：假设相机所固定的机器人连杆朝向与Z方向一致
*************************************************/
CALIBDLL_API int EyeOnHandCalib(double fixedPt[8], double rtInputPt[N_PT][8], double imageInputPt[N_PT][2], double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);
/*************************************************
  函数名:	// EyeOnHandCalibN()
  描述:		// 求n对像素坐标与机器人坐标关系的映射

  输入:		// （1）n：					n对机器人和像素坐标（限制：4<=n<=100）
            // （2）rtInputPt			相机所在关节的机器人坐标值
            // （3）imageInputPt：		对应的像素坐标值
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；请检查有无重合点
                      2；n超范围
//注意事项：假设相机所固定的机器人连杆朝向与Z方向一致
*************************************************/
CALIBDLL_API int EyeOnHandCalibN(int n, double rtInputPt[][8], double tcPt[2][8], double imageInputPt[][2], double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);
/*************************************************
  函数名:	// EyeOnHandCalibN2()
  描述:		// 求n对像素坐标与机器人坐标关系的映射

  输入:		// （1）n：					n对机器人和像素坐标（限制：4<=n<=100）
            // （2）rtInputPt			法兰盘中心对应的机器人坐标值（无工具）（基坐标系）
            // （3）tcPt				两点求工具参数（基坐标系）
            // （4）imageInputPt：		对应的像素坐标值
            // （5）usrParam			标定平面（即工作平面）所在的用户坐标系
  输出:		// （1）标定参数：CalMatrix
               （2）标定误差：err_Param
  返回值:	// 成功：0；
            // 不成功：1；九个标定点有重合点
                       2；n超范围
                       3；基准点选择不合适
*************************************************/
CALIBDLL_API int EyeOnHandCalibN2(int n, double rtInputPt[][8], double tcPt[3][8], double imageInputPt[][2], double usrParam[6],
                                  double CalMatrix[3][3], VISION_ERR_PARAM *err_Param);

/*************************************************
  函数名:	// EyeToHandCalc()
  描述:		// 已知像素坐标，计算机器人的坐标（x，y）
  功能:		// 计算机器人的坐标（x，y）

  输入:		// （1）imagePt：				待计算像素坐标（u，v）
            // （2）imgAngle：				待计算图像角度(单位：deg)
            // （3）calMat：				标定参数3*3矩阵
  输出:		// （1）rtPt：					机器人的坐标（x，y）
            // （2）rtAngle：				机器人的角度(单位：deg)
  返回值:	// 成功：0；
            // 不成功：1；请检查输入矩阵是否正确
*************************************************/
CALIBDLL_API int EyeToHandCalc(double imagePt[2], double imgAngle, double calMat[3][3], double rtPt[2], double *rtAngle);
/*************************************************
  函数名:	// EyeToHandCalc2()
  描述:		// 已知像素坐标，计算机器人的坐标（x，y，z，a，b，c）
  功能:		// 计算机器人的坐标（x，y，z，a，b，c）

  输入:		// （1）imagePt：				待计算像素坐标（u，v）
            // （2）imgAngle：				待计算图像角度(单位：deg)
            // （3）h：						目标点相对于标定平面的偏移高度
            // （4）usrParam				标定平面（即工作平面）所在的用户坐标系
            // （5）calMat：				标定参数3*3矩阵
  输出:		//  rtPt：					机器人的坐标（x，y，z，a，b，c）
  返回值:	// 成功：0；
            // 不成功：1；请检查输入矩阵是否正确
*************************************************/
CALIBDLL_API int EyeToHandCalc2(double imagePt[2], double imgAngle, double h, double usrParam[6], double calMat[3][3],
                                double rtPt[6]);

/*************************************************
  函数名:	// EyeOnHandCalc()
  描述:		// 已知像素坐标，计算机器人的坐标（x，y）
  功能:		// 计算机器人的坐标（x，y）

  输入:		// （1）camfixedPt：			相机安装关节的位姿
            // （2）imagePt：				待计算像素坐标（u，v）
            // （3）imgAngle：				待计算图像角度(单位：deg)
            // （4）calMat：				标定参数3*3矩阵
  输出:		// （1）rtPt：					机器人的坐标（x，y）
            // （2）rtAngle：				机器人的角度(单位：deg)
  返回值:	// 成功：0；
            // 不成功：1；请检查输入矩阵是否正确
*************************************************/
CALIBDLL_API int EyeOnHandCalc(double camfixedPt[8], double imagePt[2], double imgAngle, double calMat[3][3], double rtPt[2], double *rtAngle);

/*************************************************
  函数名:	// EyeOnHandCalc2()
  描述:		// 已知像素坐标，计算机器人的坐标（x，y，z，a，b，c）
  功能:		// 计算机器人的坐标（x，y，z，a，b，c）

  输入:		// （1）camfixedPt：			相机安装关节的位姿
            // （2）imagePt：				待计算像素坐标（u，v）
            // （3）imgAngle：				待计算图像角度(单位：deg)
            // （4）h：						目标点相对于标定平面的偏移高度
            // （5）usrParam				标定平面（即工作平面）所在的用户坐标系
            // （6）calMat：				标定参数3*3矩阵
  输出:		//  rtPt：					机器人的坐标（x，y，z，a，b，c）
  返回值:	// 成功：0；
            // 不成功：1；请检查输入矩阵是否正确
*************************************************/
CALIBDLL_API int EyeOnHandCalc2(double camfixedPt[8], double imagePt[2], double imgAngle, double h, double usrParam[6],
                                double calMat[3][3], double rtPt[6]);