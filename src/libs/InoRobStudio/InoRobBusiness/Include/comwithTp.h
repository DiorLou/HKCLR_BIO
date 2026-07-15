#pragma once
/**
 * 立即指令 指令类型宏定义
 **/
#define MODE_SET      0x0010  // 模式设置 1->示教 2->在线 3->示教检查 4-> 回零
#define CR_MODE_SET   0x0011  // CR模式设置 1->手动低速 2->手动高速 3->自动
#define STEP_MODE_SET 0x0012  // 寸动等级（0-无寸动，1-G1，2-G2，3-G3，4-U）

// 8个轴的状态都是按下1 弹起0 */
#define AXIS_MOVE_FORWORD 0x0020  // 激活机械单元轴正向运动（点动 or 寸动）
#define AXIS_MOVE_REVERSE 0x0021  // 激活机械单元轴反向运动（点动 or 寸动）
#define AXIS_MOVE_STOP    0x0022  // 激活机械单元轴单向运动停止（点动 or 寸动）

/****rocker*****/
#define AXIS_GROUP1_J123_XYZ 0x0121  // axis_group 1:J123/XYZ
#define AXIS_GROUP2_J456_ABC 0x0122  // axis_group2:J456/RxRyRz
// #define AXIS_GROUP3_EXT          0x0123        // axis_group3:ext_axis78

#define COORD_ADJUST 0x0124  // 姿态校准,坐标系运动矫正
#define RESUME_SPEED 0x0125  // 恢复手动高速模式下的速度

#define MOTOR_ENABLE   0x0130  // 电机使能->1  复位->0
#define PRE_COORDINATE 0x0140  // 1 2 3 4 关节，直角，工具，工件
#define ACTIVE_TOOL_NO 0x0141  // 激活工具号
#define ACTIVE_WOBJ_NO 0x0142  // 激活工件号
#define ACTIVE_LOAD_NO 0x0143  // 激活负载号

#define PRE_VEL_GRADE   0x0150  // 1 2 3 4 速度等级
#define START           0x0160  // 启动
#define MULTI_START     0x0161  // 多任务启动
#define STOP            0x0170  // 停止
#define MULTI_STOP      0x0171  // 多任务停止
#define STEP_GO         0x0180  // 单步前进
#define STEP_BACK       0x0190  // 单步后退
#define SUSPEND         0x0191  // 暂停
#define MULTI_SUSPEND   0x0192  // 多任务暂停
#define PRE_CURSOR_LINE 0x01A0  // 光标所在行号 1至无穷
#define EMERG_STOP      0x01B0  // 急停 TRUE FALSE
#define TP_ERROR        0x01C0  // 故障 0至1000
#define RESET_ARM       0x01D0  // 复位
#define START_HOMING    0x01D1  // 启动回零修复
#define REAL_CLEAR      0x01D2  // 清除报警
#define CLEAR_PLC_CFG   0x01D3  // 清除plc配置
#define CLEAR_MAX_CUR   0x01D4  // 清空最大电流数据

#define SAVE_PROJCONFIG_NOTICE 0x04A6  // 保存工程配置的通知

#define SN_RESET           0x01D7  // SN码重置
#define CLEAR_TEMP_PROJECT 0x01D8  // 清空工程临时目录
#define CLEAR_MAX_LOAD     0x01D9  // 清空最大过载数据

#define SEVENAXIS_DRAG_TEACHING     0x0C1F //七轴拖动示教
#define SEVENAXIS_GETPOINT          0x0C1E //七轴取点
#define V1R1_ROTPARAM               0x0D10 //仿生臂机器人杆件旋转角度
/**
 * 非实时指令 指令类型宏定义 指令状态：1->发送 2->接收
 **/
// 0x0200--0x020F
//  轴空间参数结构传输
#define REDUCTION_RATION 0x0200  // 减速比
// 0x0201--0x020F
#define SAVE_PARAFILE   0x0201  // 保存参数文件设置标志 1->保存 0->未保存
#define DEFAULTI_BACKUP 0x0202  // 备用参数 int16_t 示教器及InoRobotLab用于判断DSP插补是否到位，控制器没有实现代码 20200824

#define MAN_PASSWORD       0x0203  // 密码 10个字符
#define CUSTOM_STEP_MOTION 0x0204  // 自定义寸动步长（关节、笛卡尔、姿态步长下的步长）
#define DEFAULTD_BACKUP    0x0205  // 备用参数 double（第一个double为姿态寸动步长）
#define IO_ONUM            0x0206  // 工位预约指定输出IO
#define IO_INUM            0x0207  // 工位预约指定输入IO
#define PROJNAME1          0x0208  // 工位预约指定程序
#define PROJNAME2          0x0209  // 工位预约指定程序
#define PROJNAME3          0x020A  // 工位预约指定程序
#define PROJNAME4          0x020B  // 工位预约指定程序
#define PROJNAME5          0x020C  // 工位预约指定程序
#define ROBOT_WORK_MODE    0x020D  // 机器人工作模式 0：误操作，1：测试模式，2：正常模式，3：整机出厂测试，4工位预约
#define DSP_ERR_LINE       0x020E  // DSP报警行号
#define COMM_PORT          0x020F  // 通讯端口 0：客户端 其他端口：服务器

#define ABS_ZERO 0x0210  // 绝对零点位置
// 补充temp参数1
#define MESSAGE_FLAG 0x0211  // 消息 0：无消息，1：有消息并打印，2清空消息：
#define DEFAULTTD    0x0212  // 备用参数 DefaultTD
#define PCPRIN       0x0213  // PCPrin[60];// 向PC打印信息；
// 直接运动/寸动功能
#define DECTMOTION             0x0214  // 直接运动/寸动功能；
#define HOMING_J3_TORQUE_LIMIT 0x0215  // 回零J3轴转矩限制
#define INTERFERENCE_ACTIVE    0x0216  // 干涉区激活
#define REMOTE_PROJ_VEL        0x0217  // 工位预约程序速度（切换到远程IO/远程modbus权限时写入）
#define TRANSFOR_CMD           0x0218  // 需要译码命令
#define CTRL_AUTHORITY         0x0219  // 备用参数 int16_t
#define VISUALCOORD            0x021A  // 视觉标定参数
#define ALARMINF               0x021B  // 自定义报警alarm
#define INTERVAREAC            0x021C  // 干涉区
#define QUITPROGRAM            0x021D  // 程序退出
// #define DECTMOTION_PARA           0x021E        // 启动直接运动
// #define DECTMOTION_STOP		      0x021F     	// 停止直接运动
#define J4_ZERO_REPAIR 0x022E  // 启动J4回零修复
#define DIR_MOVE_ROBP  0x0221  // 启动直接运动P
#define DIR_MOVE_JP    0x0222  // 启动直接运动J
#define STOP_DIR_MOVE  0x0223  // 停止直接运动
#define DIR_MOVE_STS   0x0224  // 点运动到位状态
#define POS_FORMAT     0x0225  // 点位置的显示格式
#define GO_ZERO_START  0x0226  // 机械单元开始回零
#define GO_ZERO_STOP   0x0227  // 机械单元停止回零

#define POS_LIM   0x0220  // 正极限限位
#define NEG_LIM   0x0230  // 负极限限位
#define MAX_VEL   0x0240  // 最大允许速度,deg/s
#define T_MAX_VEL 0x0241  // 示教最大允许速度,deg/s
#define MAX_ACC   0x0250  // 最大允许加速度,deg/s*s
#define T_MAX_ACC 0x0251  // 示教最大允许加速度,deg/s*s
#define STOP_DEC  0x0260  // 停机减速度,deg/s*s

// 0x0261--0x026F
#define MOTOR_DIR            0x0261  // 电机旋转方向修正  取值0／1
#define ENC_BIT              0x0262  // 编码器位数设置
#define COUPPARAM            0x0263  // 耦合参数设置
#define ERRPOS               0x0264  // 跟随误差
#define ERRBAND              0x0265  // 到位误差
#define ERRBANDTIME          0x0266  // 到位误差保持的时间
#define ROTPARAM             0x0267  // 机器人杆件旋转角度
#define ROTCOUPPARAM         0x0268  // 机器人杆件旋转角度补偿(不再用，待团队确认)
#define SERVO_PID            0x0269  // 伺服PID参数
#define TRQ_MAX_LIMIT        0x026A  // 最大力矩限制
#define TRQ_AVRG_LIMIT       0x026B  // 平均力矩限制
#define PC_RCSYS_UPDATE      0x026C  // InoRobotLab的控制器系统升级功能
#define PC_CFG_BACKUP_LOAD   0x026D  // InoRobotLab的配置文件备份/加载功能
#define PC_BREAK_DEBUG       0x026E  // InoRobotLab的断点调试标志及状态
#define SYNC_PROJECT_DOWN    0x026F  // 下载同步工程信息
#define SYNC_PROJECT_UPON    0x0271  // 上传同步工程信息
#define SYNC_PROJECT_FLAG    0x0272  // 同步是否完成标志
#define PROJECT_NEED_RETRANS 0x0273  // 工程需要重新译码
#define ACT_PROJECT_CHANGE   0x0274  // 切换激活工程

#define MODIFY_P_INDEBUG       0x0275  // 调试中修改P点
#define MODIFY_J_INDEBUG       0x0276  // 调试中修改J点
#define FTP_PROJECT_BEGIN_FALG 0x0277  // 工程是否可进行FTP操作
#define PROGRAM_FILES_COUNT    0x0278  // 程序文件数量

#ifdef COBOT
    #define NEW_PROJECT    0x0C16  // 协作示教器 新增工程（复制一份空工程）
    #define DELETE_PROJECT 0x0C17  // 协作示教器 删除工程
    #define RENAME_PROJECT 0x0C18  // 协作示教器 重命名工程
    #define PASTE_PROJECT  0x0C15  // 协作示教器 粘贴工程（复制一份已有工程）
#else
    #define NEW_PROJECT    0x0281  // 示教器2.0 新增工程（复制一份空工程）
    #define DELETE_PROJECT 0x0282  // 示教器2.0 删除工程
    #define RENAME_PROJECT 0x0283  // 示教器2.0 重命名工程
    #define PASTE_PROJECT  0x0284  // 示教器2.0 粘贴工程（复制一份已有工程）
#endif

#define RESET_ZEROPOINT    0x0C1D  // 协作示教器 重设零点

#define REQUIRE_CONTROLLER_RELOAD_BREAKPOINTS 0x0C30  // 协作示教器 请求控制器更新断点文件
#define REQUIRE_CONTROLLER_ENABLE_BREAKPOINTS  0x0C31  // 协作示教器 请求控制器禁用/启动所有断点

#define REQUIRE_CONTROLLER_SET_STARTLINE 0x0C32 // 协作示教器 设置工程启动行

#define MODIFY_PTS_DATA   0x0285  // 批量改点 - 下发所有相关参数
#define MODIFY_PTS_STATUS 0x0286  // 批量改点 - 回读批量改点状态（0-正在计算，1-成功，2-失败，对应枚举ModifyPtsStatus）

#define FLAG_PLIM          0x0270  // 正极限标志
#define FLAG_NLIM          0x0280  // 负极限标志
#define FLAG_ENABLE        0x0290  // 使能标志
#define VEL_LIM            0x02A0  // 速度超限
#define MOTOR_STATE        0x02B0  // 运动/停止状态
#define AXIS_DIR           0x02C0  // 方向
#define IN_POS             0x02D0  // 到位
#define CUR_JOINT_P        0x02E0  // 当前位置关节点
#define CUR_ROBOT_P        0x02E1  // 当前位置笛卡尔点
#define ACTUAL_VEl         0x02F0  // 当前速度,deg/s
#define ACTUAL_CUR         0x0300  // 当前电流,mA
#define ACTUAL_AVGCUR_RATE 0x0301  // 当前(实时)负载率

#define AMBIENT_TEMPERATURE    0x0302  // 环境温度
#define MOTOR_OVERHEAT_RATIO   0x0303  // 点击过热率百分比
#define ENCODER_OVERHEAT_RATIO 0x0304  // 编码器过热率百分比
#define OVERLOAD_ACTUAL_RATIO  0x0305  // 过载率当前值占比
#define OVERLOAD_MAX_RATIO     0x0306  // 过载率最大值占比
#define OVERHEAT_LIMIT         0x0307  // 过热率限制
#define OVERLOAD_LIMIT         0x0308  // 过载率限制
#define OVERHEAT_SUPPORTFLAG   0x0309  // 是否支持温升保护
#define WARM_UP_MACHINE_PARAM  0x030A  // 自动热机参数
#define WARM_UP_MACHINE_INFO   0x030B  // 自动热机实时信息

#define CURR_POS          0x0310  // 当前计算位置,deg
#define ACTUAL_MOTOR_POS  0x0320  // 当前各电机位置（编码器绝对位置，DSP读取时对波动做判断）
#define SERVO_PARA_UPDATE 0x0322  // 请求读取伺服类参数,伺服参数界面离开时示教器必须要发停止                                          // S18T02需读取伺服参数界面：电流保护（0x0301）、伺服参数（0x0450）
// #define DEF_TRQ_MAX_LIMIT       0x0323        // 系统默认最大力矩限制
// #define DEF_TRQ_AVRG_LIMIT      0x0324        // 系统默认平均力矩限制
#define MAX_CUR_PERCENT       0x0325  // 电流最大值百分比 = 电流最大值/（默认最大力矩*0.1*界面设置百分比*指令设置百分比）
#define ACTUAL_AVGCUR_PERCENT 0x0326  // 实时负载率百分比 = 实时负载率/（默认平均力矩*0.1*界面设置百分比*指令设置百分比）
#define ACTUAL_CUR_PERCENT    0x0327  // 实时电流百分比 = 实时电流/（默认平均力矩*0.1*界面设置百分比*指令设置百分比）
#define COLLISION_LEVEL       0x032C  // 碰检等级

// 笛卡尔坐标系空间参数结构传输
#define CPOSITION_ACC_TIME     0x0330  // ,us
#define CPOSITION_NUM_AXIS     0x0331  // 4 5 6
#define CPOSITION_DEFAULT_PARA 0x0332  // 1恢复默认值 0保持变化
#define CLEAR_ERRRECORD        0x0333  // 清除历史报警文件
#define R_ROBOT_NAME           0x0334  // 读取机器人名称
#define ENTER_BREAK_FLAG       0x0335  // 进入断点标志位

#define TOOL_DATA 0x0340  // 工具参数
#define WOBJ_DATA 0x0341  // 工件参数
#define LOAD_DATA 0x0342  // 负载参数
#define ARMLOAD   0x0343  // 臂负载参数

#define LOADRANGE 0x0347  // 负载范围

#define ROBOT_PARA_ROBOT          0x0360  // 机器人结构参数
#define ROBOT_PARA_COMP           0x0361  // 机器人结构参数补偿
#define ROBOT_STIFF_PARA          0x0362  // 机器人动力学参数
#define ROBOT_FULL_PARA           0x0363  // 机器人全参参数
#define CPOSITION_MAX_VEl         0x0370  // 最大允许速度, mm/s
#define CPOSITION_TMAX_VEL        0x0371  // 示教最大允许速度, mm/s
#define CPOSITION_MAX_GVEl        0x0380  // 最大允许姿态速度,deg/s
#define CPOSITION_TMAX_GVEl       0x0381  // 示教最大允许姿态速度,deg/s
#define CPOSITION_ACC             0x0390  // 最大允许加速度,mm/s*s
#define CPOSITION_TACC            0x0391  // 示教最大允许加速度,mm/s*s
#define CPOSITION_GES_ACC         0x03A0  // 最大允许姿态加速度,deg/s*s
#define CPOSITION_TGES_ACC        0x03A1  // 最大允许姿态加速度,deg/s*s
#define CPOSITION_STOP_DEC        0x03B0  // 停机减速度,mm/s*s */
#define CPOSITION_GES_STOP_DEC    0x03C0  // 停机姿态减速度,deg/s*s
#define CPOSITION_FORCE_IO_INOUT  0x03C1  // 通用强制I/O
#define SYSTEM_FORCE_IO_INOUT     0x03C2  // 系统强制I/O
#define ZONEPARA                  0x03C6  // 过度等级姿态,deg/s*s
#define GES_ZONEPARA              0x03C7  // 过度等级,mm/s*s
#define TRACE_RECOVER             0x03C8  // 轨迹恢复 r:是否需要显示轨迹恢复选项(char:0/1); w:是否执行轨迹恢复(char:0/1)
#define CIRINTERPMODE             0x03CA  // 圆弧插补方式,deg/s*s
#define LAST_FD                   0x03CB  // 当前文件名称 char[100]
#define SET_PROG_STARTLINE        0x03CC  // 设置程序起始行（程序+起始行号）
#define CPOSITION_ACT_LC          0x03D0  // 当前位姿
#define GENERAL_IO_INOUT          0x03D1  // 通用I/O输出
#define SYSTEM_IO_INOUT           0x03D2  // 系统I/O输出
#define LATCH_IO_CFG              0x03D3  // 位置锁存（飞拍）输出Out配置
#define DYN_BRAKE_SWITCH          0x03D4  // 动态制动开关
#define EMERG_CFG_TYPE            0x03D5  // 急停方式配置
#define SN_CHECK_FLAG             0x03D6  // SN码检查开关
#define SN_RESET_STATE            0x03D7  // SN码重置状态
#define VIBRA_GYRO_CVRMODE        0x03D8  // 陀螺仪振动抑制模式
#define VIBRA_GYRO_ERRMODE        0x03D9  // 陀螺仪报警等级
#define TORQUE_RECTIFY_AUTO_LEARN 0x03DA  // 力矩模型校正自动学习
#define TORQUE_RECTIFY_PARA       0x03DB  // 力矩模型校正参数
#define SELF_LEARN_DATA_LOAD      0x03DC  // 自学习数据文件加载
#define SELF_LEARN_DATA_RESTORE   0x03DD  // 自学习数据文件恢复默认
#define SELF_LEARN_DATA_CLEAR     0x03DE  // 清除自学习数据
#define SELF_LEARN_DATA_VERSION   0x03DF  // 自学习数据文件版本
#define SELF_LEARN_DATA_TO_FILE   0x03E1  // 通知控制器将自学习数据写入到文件中
#define MODE_SPEED_LIMIT_SWITCH   0x03E2  // 模式限速开关

// 处理完全  由于之前排序调整问题对其重新定义
#define IN_MOTION      0x03E0  // 正在运动
#define MOTION_MODE    0x03F0  // 当前运动模式   手动(1)/自动(2)/错误(-1 / -2)
#define JOG_COORDINATE 0x0400  // 手动坐标系选择 关节(0)/基(1)/工具(2)/用户(3)
#define PRE_LINE_NUM   0x0410  // 当前程序行号
#define ERROR_STOP     0x0420  // 运动时的极限/奇异区域/无解等情况的停止状态

#define ARM_ERROR     0x0421  // ARM报警
#define COM_ERROR     0x0422  // 通讯端报警
#define DSP_ERROR     0x0423  // DSP报警
#define MEM_ERROR     0x0424  // 0无报警 1伺服报警
#define ERROR_WARNING 0x0425  // 警告

#define INIT_STATUS        0x0430  // 初始化运动状态完成阶段 FPGA初始化完成->1   双DSP初始化完成->2   ARM初始化完成->3
#define INIT_STATUS_SUPPLE 0x0431  // 补充初始化状态 未开始补充初始化（-1表示示教器需读取补充初始化状态）->-1  SD初始化完成->1
#define CONNECT_DEV_TYPE   0x0432  // 上位机连接类型   0 初始值   1 InoRobotLab   2 示教器
#define FACTORY_HOMING_REC 0x0433  // 工厂回零操作记录 0-无工厂回零操作记录 1-有工厂回零操作记录

#define RVLIFESPAN         0x0434  // 读取减速机寿命状态, 设置减速机寿命计算配置
#define RVLIFE_THRESHOLD   0x0435  // 读写减速机寿命阈值
#define RVLIFE_ACC_SET     0x0436  // 读写减速机加速度相关参数
#define RVLIFE_REDUCERTYPE 0x0437  // 读取各轴减速机型别

#define ROBOT_LINK_LOAD  0x043C  // 机器人臂长/负载
#define TVER_INFO_STATIS 0x043D  // 版本信息统计
#define VERSION2         0x043E
#define VERSION1         0x043F
#define ETH1_IP_CONFIG   0x0440  // 网卡1的IP地址
// #define VERSION                 0x0440        // EtherCAT版本信息 'R'-Release 'D'-Debug 'T'-Test

#define HOMING_OPT_RES         0x0441  // 回零操作&状态
#define HOMING_MUL_CIRCLE_STAT 0x0442  // 回零编码器多圈状态 0-正常 1-多圈
#define HOMING_OFFSET          0x0443  // 回零偏置读写

#define ECAT_COM_CYC          0x0444  // EtherCAT通信周期设置 一般250us倍数不会多于10ms
#define ECAT_VER_SEL          0x0445  // EtherCAT版本信息 'R'-Release 'D'-Debug 'T'-Test
#define SERVO_SLAVEOP_MODE    0x0446  // servo slaves operational mode: 8-csp 9-csv 10-cst
#define ECAT_SLAVE_NUM        0x0447  // io slaves numbers need to be configured in system (Most 4)
#define ECAT_MODULE_PARA      0x0448  // 模块参数设置
#define ECAT_READ_MODULE_PARA 0x0449  // 重新上电预读回之前存储的I/O参数

#define LOGSWITCH_FUNC     0x044A  // logswitch 功能
#define MODBUSWRT          0x044B  // 示教器读写modbus功能
#define PVALWRF            0x044C  // 重新加载P变量
#define ECAT_PDO_FDERR_CNT 0x044D  // EtherCAT(servo)丢帧计数
#define SERVO_FUNCODE_OPT  0x044E  // 伺服读写
#define SERVO_FUNMODE      0x0450  //
#define SET_GET_TIMER      0x0451  // 设置与获取控制器时间

/*新添加irlink指令*/
#define IRLINK_COM_CYC            0x0452  // irlinkEtherCAT通信周期设置 一般250us倍数不会多于10ms
#define IRLINK_VER_SEL            0x0453  // irlink版本信息 'R'-Release 'D'-Debug 'T'-Test
#define IRLINK_SERVO_SLAVEOP_MODE 0x0454  // servo slaves operational mode: 8-csp 9-csv 10-cst
#define IRLINK_SLAVE_NUM          0x0455  // io slaves numbers need to be configured in system (Most 16)
#define IRLINK_MODULE_PARA        0x0456  // 模块参数设置
#define IRLINK_READ_MODULE_PARA   0x0457  // 重新上电预读回之前存储的I/O参数

// 机器人原点参数
#define ROBOT_ORIGIN_POINT_PARA        0x0458  // 机器人原点参数
#define IRLINK_RTU_PARA                0x0459  // IRLinkRTU框架信息
#define ELECTRIC_CABINETS_CONF         0x045A  // 机器人电控柜配置 1:原来配置类型 2:小多传配置类型 3:20kg立柜
#define ROBOT_ORIGIN_POINT_OFFSET_PARA 0x045B  // 机器人原点触发out信号参数

#define SD_LOAD_STAT    0x045F  // 读取存储卡加载状态
#define SD_FORMAT       0x0460  // 格式化存储卡
#define CALL_SUB_PROGAM 0x0461  // 调用子程序

#define RUNTIMEN      0x0462  // 时间计数
#define DELTAHOMELIM  0x0463  // DELTAHOMELIM
#define MACHINEMOTION 0x0464  // 机器人锁定状态
#define STATESAVE     0x0465  // 机器人状态保存与下载
#define ZHENTYPE      0x0466  // 机器人语言
#define CUREXTMCH     0x0467  // 当前执行通道
#define GCHARVAL      0x0468  // 全局字符串变量
#define MAINPROSTAT   0x0469  // 主程序名及状态

#define SYSPING1 0x046A  // 系统ping功能（读写ip地址/写ip设置参数）
#define SYSPING2 0x046B  // 读ping结果
#define SERIALSW 0x046C  // 串口开关

#define DIAGNOSTIC_SAVE_OPT   0x046D  // 系统诊断保存操作
#define DIAGNOSTIC_EXPORT_OPT 0x046E  // 系统诊断导出操作

#define SAFEDOOR_CFG 0x046F  // 安全门配置

#define VISUALIPNUM 0x0470  // 视觉测试IP及端口
#define VISUALPARA  0x0471  // 触发方式参数
#define VISUALSRD   0x0472  // 发送/接受数据

#define VELPRE        0x047A  // 全局最大速度百分比
#define ACCPRE        0x047B  // 全局最大加速度百分比
#define CAMERALNAME   0x047C  // 相机名称
#define MULTI_LASTFD  0x047D  // 多任务名称
#define MULTI_STCTASK 0x047E  // 静态任务使能
#define MULTI_DYCTASK 0x047F  // 动态任务使能

#define IOOUTSTATE 0x0480  // 输出IO权限属性
// 20191031y3489
#define SERVOINFO   0x0481  // 伺服信息(包括IP地址、端口、和轴数)
#define DASTATE     0x0482  // 输出DA权限属性
#define ADSTATE     0x0483  // 输出AD权限属性
#define IRLINKSTATE 0x0484  // IRLink配置权限属性

#define DAREAD  0x0486  // 读取DA/AD信息
#define DAWRITE 0x0487  // 写入DA/AD信息

#define SCREW_PARA_SET       0x0488  // 锁螺丝参数设置(读写伺服)
#define UNLOCKSCREW_PARA_SET 0x0489  // 拆螺丝参数设置(读写伺服)
#define SCREW_PARA_DIS       0x0490  // 锁螺丝数据显示
#define SCREW_COUNTER_CLEAR  0x0491  // 锁螺丝计数器清零
#define SERVO_ENCODER_RESET  0x0492  // 伺服编码器复位
#define SERVO_CHECK_SWITCH   0x0493  // 伺服参数安全检查开关
#define CURRENT_SYS_MODE     0x0494  // 查询机器人当前系统模式

#define GROUP_RTDATA               0x049A  // 新组合的周期数据
#define GROUP_INITIALDATA          0x049B  // 新组合的开机数据
#define SET_TP_EMERG_METHOD        0x049C  // 设置急停方式
#define MULTI_TASK_CFG             0x049D  // PC编译平台, 任务激活状态设置
#define MULTI_TASK_STA             0x049E  // PC编译平台, 读取多任务运行状态
#define DYNAMIC_BRAKE              0x049F  // 写动态制动状态
#define RC_VERSION                 0x04A0  // 控制器版本名
#define BRAKE_FUNTION              0x04A1  // 松抱闸功能
#define LOAD_IDENTIFY_RESULT       0x04A2  // 负载辨识结果
#define LOAD_IDENTIFY_STATUS       0x04A3  // 终止负载辨识/获取读取负载辨识状态
#define IDENTIFY_GET_TRAJPOINT     0x04A4  // 获取控制器存储的轨迹点值（V4R24C3版本后引入）
#define IDENTIFY_GET_RECOMMENPOINT 0x04A5  // 获取某条轨迹的推荐值（V4R24C3版本后引入）
#define PrjConfig                  0x04A6  // 工程序号配置
#define ROBOT_POINT_ID_CONFIG      0x04A7  // 位置点位文件序号配置
#define TP_KEY_TRIGGER_MODE        0x04A8  // 位置示教器钥匙开关触发方式配置

#define AUTH_ACTIVE_FUNCTION 0x04B0  // auth & active function by maxmin chip
#define AUTH_GETROMID        0x04B1  // PC/TP read maxmin chip rom id 8 bytes
#define AUTH_GETETAG         0x04B2  // PC/TP read maxmin chip e-tag id 8 bytes
#define AUTH_GETUSERDATA     0x04B3  // PC/TP read maxmin chip user data 32bytes
#define AUTH_GETBOARDSN      0x04B4  // S/N 64bytes

#define AUTH_ECAT_SLAVE_AUTHSTATUS 0x04B5  // EtherCAT从站是否生效
#define AUTH_ECAT_CHIP_EXIST       0x04B6  // 是否存在EtherCAT从站芯片
#define AUTH_GETAUTHRESULT         0x04B7  // 加密授权认证是否通过

// 零点校准
#define ZERO_CALIB_SUPPORT                        0x044F  // 是否支持零点校准功能（六关节）
#define ZERO_POINT_PARAM                          0x04C1  // 零点参数（读）
#define ZERO_POINT_COLLISION_TOOL_TYPE            0x04C2  // 碰撞工具类型（读）
#define ZERO_POINT_CALCULATE_ZERO_PARAM_DEVELOPER 0x04C3  // 计算开发者模式的零点参数（写）
#define ZERO_POINT_CALIBRATE_LOAD_NUMBER          0x04C4  // 负载号（读、写）
#define ZERO_POINT_SENSOR_STATUS_CHECK            0x04C5  // 触发传感器状态监测（写）
#define ZERO_POINT_READ_JPOS_PRE                  0x04C6  // 预校准位置（读）
#define ZERO_POINT_WRITE_DEVELOPER_MODE           0x04C7  // 进入开发者模式（写）
#define ZERO_POINT_WRITE_KB_MODE                  0x04C8  // 零点参数模式（写）
#define ZERO_POINT_WRITE_KB_CALCULATE             0x04C9  // 零点参数计算指令（写）
#define ZERO_POINT_WRITE_KB_APPLY                 0x04CA  // 零点参数应用指令（写）
#define ZERO_POINT_WRITE_KB_RESET                 0x04CB  // 零点参数重置指令（写）
#define ZERO_POINT_UPDATE_ZEROSLOT_POS            0x04F9  // 更新零点卡槽位置
#define ZERO_POINT_CALIB_DOWEL_CHECK              0x04FA  // 零点校准定位销拆卸检查
#define ZERO_POINT_CALIB_STOP_CHECK               0x04FB  // 零点校准定位销停止验证
#define ZERO_POINT_CONTROLLER_IS_35KG_TYPE        0x04FC  // 35kg机型检查
#define ZERO_POINT_CALIB_LOAD_MODE                0x04FD  // 零点校准负载模式读写
#define ZERO_POINT_CALIB_LOAD_OFFSET              0x04FE  // 零点校准负载偏置读写
#define RECORD_CURRENT_POSITION                   0x04FF  // 记录零点卡槽位置
#define ZERO_POINT_REPAIR_CALIB                   0x04D0  // 获取零点标定结果
#define ZERO_POINT_REPAIR_VISIBLE                 0x04D1  // 获取零点标定界面是否在用户模权限下可见

#define STATION_RESERVE_MODE  0x04E0  // 工位预约模式设置
#define STATION_RESERVE_STATE 0x04E1  // 工位状态
#define STATION_RESERVE_RESET 0x04E2  // 重置工位

#define GENERIC_NET_SET 0x05B4  // 设置通用通讯参数

/**
 *大文件指令 指令类型宏定义
 **/
#define MKDIR         0x0500  // 创建目录
#define RENAME_DIR    0x0510  // 目录重命名
#define RMDIR         0x0520  // 删除目录
#define SOLE_SEND_DIR 0x0530  // 单级发送目录
#define MUL_SEND_DIR  0x0540  // 多级发送目录
#define CP_DIR_FILE   0x0541  // 拷贝文件或者目录
#define MV_DIR_FILE   0x0542  // 剪切文件或者目录

#define MKFLIE      0x0560  // 创建文件
#define FILEENC     0x0561  // 文件加密
#define RENAME_FILE 0x0570  // 文件重命名
#define RMFILE      0x0580  // 删除文件
#define RECV_FILE   0x0590  // 控制器接收文件

#define RECV_FILE_OTHER 0x0591  // 控制器接收文件
#define SEND_FILE_OTHER 0x0592  // 控制器接收文件

#define GET_FILE_OR_FOLDER_SIZE 0x0593  // 获取控制器中指定文件或者文件夹大小，kb为单位

#define SEND_FILE    0x05A0  // 控制器发送文件
#define READ_REALCMD 0x05A1  // 读实时指令  用大文件

// 定义出第三方指令
#define RW_R_CMD  0x05A2  // 读写R变量     用大文件
#define RW_PR_CMD 0x05A3  // 读写PR变量    非实时

// 测试软件部分
#define TEST_EMC_CMD 0x05A4  // 测试软件协议部分
#define READ_B_CMD   0x05A5  // 读写B变量     用大文件
#define READ_D_CMD   0x05A6  // 读写D变量     用大文件

#define READ_LB_CMD     0x05A7  // 读写LB变量     用大文件
#define READ_LR_CMD     0x05A8  // 读写LR变量    	用大文件
#define READ_LD_CMD     0x05A9  // 读写LD变量     用大文件
#define READ_PALLET_CMD 0x05AA  // 读写pallet变量     用大文件

#define VISUALSTRT         0x05AC  // 读写视觉标定字符串     用大文件
#define VISUALCOMPEN       0x05AD  // 读写视觉误差     用大文件
#define READ_SCREW_PROFILE 0x05AE  // 锁螺丝轨迹数据	用大文件
// #define COLLISION_PARAM	        0x05AF	      // 碰撞检测数据	用大文件

#define NEW_READ_B_CMD 0x05B0  // 读写B变量(单类型非连续Ｂ变量读取)     用大文件
#define NEW_READ_R_CMD 0x05B1  // 读写R变量（单类型非连续Ｒ变量读取）     用大文件
#define NEW_READ_D_CMD 0x05B2  // 读写D变量（单类型非连续D变量读取）     用大文件

#define NEW_READ_BRD_CMD   0x05B3  // 读写BRD变量（多类型非连续BRD变量读取）     用大文件
#define GENERIC_NET_STAT   0x05B4  // 通用网络状态监控     用大文件
#define MOTOR_PROTECT_PARA 0x05B5  // 读写电机失稳保护参数   用大文件

#define READ_MULTI_TASK_RUN_INFO 0x05B6  // 读实时多任务运行信息
#define GET_CUR_TASK_SUB_FUNC    0x05B7  // 获取当前任务中的所有子程序名称
#define SET_BRDP_VALUE           0x05B8  // 设置全局变量值
#define BREAK_INFO               0x05B9  // 断点信息
#define SET_VAR_ATPP_INTASK      0x05BA  // 设置变量的值（当前启动行处、某个任务中，可以是全局变量或局部变量）
#define MOUSE_MONITOR_STR        0x05BB  // 监控鼠标放置的变量的值

#define ROBOT_POINT_FILE_NAME  0X05BC  // 获取当前加载的位置点位文件名称
#define ROBOT_SAVE_POINTS_NAME 0X05BD  // 获取当前SavePoints指令执行的点位文件名称

#define RW_ROBP_CMD   0x05C1  // 读RobP变量内存值
#define INQUIRE_P_CMD 0x05C2  // 跳转查询gp变量   用大文件
#define RW_JP_CMD     0x05C3  // 读JP变量内存值
#define CALC_PR_CMD   0x05C4  // 计算PR变量    用大文件

// DSP参数
#define DSP_PARAM 0x05D0  // 读写DSP参数

#define LOAD_IDENTIFY_DATA 0x05D1  // 负载辨识数据

#define MAINTAIN_REMINDER_MSG 0x05E0  // 读写机器人维护状态

#define CVYBASEPARA                               0x0610  // 传送带基本参数；
#define CNVOR_BASE_PARA                           0x0611  // 传送带参数设置命令
#define CNVOR_BELT_POS_PARA                       0x0612  // 传送带位置
#define CNVOR_MONITOR_DATA                        0x0613  // 传送带监控数据
#define CNVOR_CLEAR_WORKPIECE_BEYOND_BOUNDARY_NUM 0x0614  // 清空工件超界数
#define CNVOR_OFFSET                              0x0615  // 计算偏移后示教点
#define CNVOR_CALIBRATION                         0x0616  // 计算标定矩阵和误差
#define CNVOR_VISION_PARA                         0x0617  // 传送带视觉通讯参数
#define CNVOR_EYE_TO_HAND_POINT                   0x0618  // 将视觉点转化为传送带坐标系下点

#define RW_INTERFER_ZONE_TOOLWOBJPARAM 0x0619  // 读写干涉区工具工件相关

#define RW_SOFEMOVE_PARA 0x061A  // 读写软浮动参数（大文件）
// #define CVYENCODE                 0x0620        // 传送带编码器分辨率；
// #define CVYBORDERPARA             0x0630        // 传送带视窗边界参数；
// #define CVYVISUALPARA             0x0640        // 传送带视觉参数；
// #define CVYSENSORPARA             0x0650        // 传送带传感器参数；
// #define CVYPOS                    0x0660        // 传送带当前位置；
// #define SENSORCVYPOS              0x0670        // 传感器触发时传送带位置；

#define RW_INTERFER_ZONE_ACT_STAT 0X061B  // 干涉区激活状态
#define RW_INTERFER_ZONE_PARA     0x061C  // 干涉区V25版本读写
#define RW_INTERFER_TOOL_ACT_STAT 0x061D  // 监控对象激活状态
#define RW_INTERFER_TOOL_PARA     0x061E  // 干涉区末端监测对象V25版本读写

#define RW_TRAJRECOVERY_PARA                 0x0629  // 轨迹恢复阈值设置
#define READ_MULTI_FUNC_STATE                0x062A  // 获取独立轴、外部轴、视觉一拖多功能的开关状态
#define READ_OTM_ALL_SLAVE_CONNECT_INFO      0x0620  // 读取主控列表中所有从控的IP、端口、连接状态
#define WRITE_OTM_DISCONNECT_ALL_SLAVE       0x0621  // 主控断开所有从控的连接
#define WRITE_OTM_CONN_AND_DISCONN_TO_MASTER 0x0622  // 从控与主控连接/断开连接
#define READ_OTM_MASTER_OR_SLAVE_IP_AND_PORT 0x0623  // 查询主控或从控所使用的IP和端口
#define WRTIE_OTM_BELT_INDEX                 0x0624  // 通知下位机视觉监控的传送带编号
#define READ_OTM_REMOTE_CONNECT_INFO         0x0625  // 视觉监控功能读取远端设备IP、端口和连接状态
// #define READ_OTM_VISION_DATA_SLAVE                  0x0626  //从控读视觉一拖多监控数据 弃用
#define READ_OTM_VISION_DATA_MASTER 0x0627  // 主控读视觉一拖多监控数据

#define RW_FORE_CTRL_CONFIG_PARA 0x0630  // 读写力控配置参数（大文件）
#define RW_FORE_CTRL_MOVE_PARA   0x0631  // 读写力控控制参数（大文件）
#define RW_FORE_CTRL_SET_PARA    0x0632  // 通知力控标定参数下发（非实时）
#define RW_FORE_CTRL_ORIG_VALUE  0x0633  // 读写力控六个力（非实时）
#define RW_FORE_CTRL_CILIB       0x0634  // 力控标定计算（大文件）
#define RW_FORE_CTRL_FUNC_SWITCH 0x0635  // 力控开关配置（非实时）
#define RW_FORE_CTRL_COORDINATE  0x0636  // 力控坐标系配置（非实时）
#define RW_FORE_CTRL_RCOORDINATE 0x0637  // 力控坐标系读取某一组数据(大文件)
#define RW_FORE_CTRL_CONFIG      0x0638  // 力控配置参数参数下发通知（非实时）
#define RW_FORE_CTRL_MOVE        0x0639  // 力控控制参数参数下发通知（非实时）
#define RW_FORE_CTRL_LIMIT       0x063A  // 力控限制参数参数下发通知（非实时）
#define RW_FORE_CTRL_LIMIT_PARA  0x063B  // 读写力控限制参数（大文件）

#define TRAVE_SCREWFLIE_DIR 0x0700  // 遍历锁螺丝文件
#define MK_SCREWFLIE        0x0701  // 创建锁螺丝文件
#define RM_SCREWFILE        0x0702  // 删除锁螺丝文件
#define RENAME_SCREWFILE    0x0703  // 锁螺丝文件重命名
#define OPERATE_SCREWFLIE   0x0704  // 锁螺丝文件打开/保存
#define CP_SCREWFLIE        0x0705  // 锁螺丝文件复制

#define GROUP_RTDATA_V22            0x0710  // 新组合的周期数据 S03.22
#define GROUP_INITIALDATA_V22       0x0711  // 新组合的开机数据 S03.22
#define EVENTS_POLLING              0x0712  // 轮询事件列表
#define BUSIO_CUR_FBUS_SLAVE_TYPE   0x0800  // 当前激活的总线类型
#define BUS_MODBUS_CFG_STS          0x0801  // 读写Modbus配置与状态
#define BUS_EIP_CFG_STS             0x0802  // 读写EIP配置与状态
#define BUS_ECAT_SLAVE_CFG_STS      0x0803  // 读写ECAT配置与状态
#define BUSIO_FBUS_SLAVE_ADDRASSIGN 0x0804  // 读写地址分配
#define BUS_IO_MAP                  0x0805  // 读写IO映射
#define BUS_MC_ACTIVE_STS           0x0806  // 读写MC激活状态
#define BUS_MC_CONNECT_CFG          0x0807  // 单个MC连接断开配置
#define BUS_ALL_MC_CONNECT_STS      0x0808  // 所有MC连接状态
#define BUS_IO_MAP_PARA_RE_LEN      0x0809  // 总线IO映射功能码个数（包括预留）

#define BUS_PN_UPGRADE              0x080A  // Profinet启动升级
#define BUS_PN_ACTIVE_CFG           0x080B  // Profinet激活状态
#define BUS_ZERO_CODING_MODE_STATUS 0x080C  // 机器人零编程模式状态
#define BUS_ECATV2_PROP             0x080D  // ECAT新增属性
#define BUS_ECATV2_RZGD             0x080E  // ECAT合规性业务判断

#define BUSIO_INPUT_STATUS                        0x0810  // 总线输入数据（写仅限内存IO）
#define BUSIO_INPUT_FORCE_HIGH                    0x0811  // 总线输入强制为高的状态（仅限数字IO）
#define BUSIO_INPUT_FORCE_LOW                     0x0812  // 总线输入强制为低的状态（仅限数字IO）
#define BUSIO_OUTPUT_STATUS                       0x0813  // 总线输出数据
#define BUSIO_OUTPUT_BIT_STATUS                   0x0814  // 按bit读写总线输出数据
#define BUSIO_OUTPUT_CTRL_AUTHORITY_STATUS        0x0815  // IO输出的控制权
#define BUSIO_COMMON_INPUT_STATUS                 0x0816  // 常用 输入 IO
#define BUSIO_COMMON_OUTPUT_STATUS                0x0817  // 常用 输出 IO
#define BUSIO_COMMON_OUTPUT_CTRL_AUTHORITY_STATUS 0x0818  // 常用IO输出的控制权
#define COMM_VERSION_MATCH                        0x0819  // 通讯版本匹配

#define MECH_UNIT_CFG      0x0820  // 机械单元配置
#define EXT_AXIS_ZERO      0x0821  // 机械单元零点
#define MECH_UNIT_ACTIVE   0x0822  // 切换当前激活的机械单元
#define ROBOT_COOPERATE    0x0823  // 机器人协调
#define IND_AXIS_IN_USING  0x0824  // 获取实时运行的独立轴
#define IND_AXIS_RESET     0x0825  // 独立轴重置
#define MECH_UNIT_CFG_DATA 0x0826  // 机械单元配置数据
#define MWCHUNIT_AUTHORITY 0x0827  // 机械单元配置权更新
#define GET_SPOT_GUN_FLAG  0x0828  // 读取点焊代码屏蔽标志位
#define SING_AREA_HANDLE   0x0830  // 奇异穿越

#define START_MODE 0x0840  // TP|PC启动释放策略

#ifdef COBOT
    #define SCRIPT_START     0x0851  // 脚本启动
    #define SCRIPT_PAUSE     0x0852  // 脚本暂停
    #define SCRIPT_STEP      0x0853  // 脚本单步
    #define SCRIPT_ABORT     0x0854  // 脚本终止
    #define SCRIPT_STEPBLOCK 0x0855  // 脚本终止
#else
    #define SCRIPT_START 0x0850  // 脚本启动
    #define SCRIPT_PAUSE 0x0851  // 脚本暂停
    #define SCRIPT_STEP  0x0852  // 脚本单步
    #define SCRIPT_ABORT 0x0853  // 脚本终止
#endif

#define CUR_JOINT_P_ROBOT_P   0x0860  // 当前位置关节点和当前位置笛卡尔点
#define KINE_INVERSE_SOLUTION 0x0861  // 运动学逆解
#define READ_TOOL_IO_SETTING  0x0862  // 协作 读取末端io功能码配置
#define RS485_DEBUGGING       0x0863  // 协作 末端IO/电柜 RS485调试
#define READ_COBOT_ADDA_VALUE 0x0864  // 协作 读取协作电柜+末端AD DA
#define READ_FILE_MD5_IN_RC   0x0865  // 读取控制器指定路径文件的MD5
#define RS485_CONFIG          0x0866  // 协作 读/写 电柜/末端 485配置

#define CALIB_GRIPTOOLPRM_3P            0x0900  // 获取标定结果：夹持工具三点法TCP
#define CALIB_GRIPTOOLPRM_3PZX          0x0901  // 获取标定结果：夹持工具三点法TCP+ZX
#define CALIB_EXTTOOLPRM_1P             0x0902  // 获取标定结果：外部工具已知工具一点法TCP
#define CALIB_EXTTOOLPRM_1PZX           0x0903  // 获取标定结果：外部工具已知工具一点法TCP+ZX
#define CALIB_EXTTOOLPRM_3P             0x0904  // 获取标定结果：外部工具未知工具三点法TCP
#define CALIB_EXTTOOLPRM_3PZX           0x0905  // 获取标定结果：外部工具未知工具三点法TCP+ZX
#define CALIB_EXTWOBJ_USERPRM_3P        0x0906  // 获取标定结果：外部工件三点法标定用户坐标系
#define CALIB_EXTWOBJ_USERPRM_CIRLE3P   0x0907  // 获取标定结果：外部工件旋转法标定用户坐标系
#define CALIB_EXTWOBJ_OBJPRM_3P         0x0908  // 获取标定结果：外部工件三点法标定工件坐标系
#define CALIB_GRIPWOBJ_USERPRM_3P       0x0909  // 获取标定结果：夹持工件三点法标定用户坐标系
#define CALIB_GRIPWOBJ_OBJPRM_3P        0x090A  // 获取标定结果：夹持工件三点法标定工件坐标系
#define CALIB_ROBOTBASEPRM_3P           0x090B  // 获取标定结果：三点法标定机器人基坐标系
#define CALIB_POSITIONERJ1PRM_3P        0x090C  // 获取标定结果：旋转法标定单轴变位机
#define CALIB_POSITIONERJNPRM_3P        0x090D  // 获取标定结果：旋转法标定多轴变位机
#define CALIB_UNFIXED_EXTWOBJ_OBJPRM_3P 0x090E  // 获取标定结果：外部非固定工件三点法标定工件坐标系(可移动的用户坐标系下标定工件坐标系oframe)

#define CALIB_VISION_CALC9POINT     0x0910  // 获取标定结果：根据已知点求取九点位置（半自动：已知三点求九点，全自动：已知一点和距离求九点）
#define CALIB_VISION_EYEHANDCALIBN  0x0911  // 获取标定结果：四轴手眼标定
#define CALIB_VISION_EYEHANDCALIBN2 0x0912  // 获取标定结果：六轴手眼标定
#define CALIB_ROBOTBASEPRM_6P       0x0913  // 获取标定结果：六点法标定机器人基坐标系
#define CALIB_ROBOTBASEPRM_9P       0x0914  // 获取标定结果：九点法标定机器人基坐标系

#define ROBOT_PARAM_FILE_CHANGE        0x0920   // 通知机型参数文件更新
#define ROBOT_PARAM_SERVO_START        0x0921   // 启动伺服监控
#define ROBOT_PARAM_SERVO_STOP         0x0922   // 停止伺服监控
#define ROBOT_PARAM_SERVO_CURRENT      0x0923   // 获取当前伺服参数
#define ROBOT_PARAM_UPDATE_STATUS      0x0924   // 获取机型参数更新状态
#define ROBOT_PARAM_MATCH_INFO         0x0925   // 获取匹配信息
#define ROBOT_PARAM_PARAM_MATCH        0x0926   // 启动参数匹配
#define BODY_WILDCARD_INFO_STRAT       0x0927   // 启动获取本体通配信息
#define BODY_WILDCARD_INFO_STATUS      0x0928   // 本体通配信息获取状态
#define ROBOT_PARAM_GENERAL_SET_STATUS 0x0929   // 设置通配状态
#define ROBOT_PARAM_SERVO_SET          0x0930;  // 设置伺服参数

#define FORCE_CTRL_GET_DATA       0x0931;  // 从控制器获取力控的实时数据
#define FORCE_CTRL_MONITOR_SWITCH 0x0932;  // 力控实时数据监控开启与关闭
#define FORCE_CTRL_CLEAR_SENSOR   0x0934;  // 力控功能清空传感器残余应力（清零）
#define FORCE_CTRL_LOG_FORMAT     0x0935;  // 力控功能自定义日志数据
#define FORCE_CTRL_COORDINATE_SETTING     0x0936;  // 力觉坐标系设置

#define FORCE_CTRL_GET_FILE_PATH 0x0933;  // 力控功能获取导出日志的本地路径

#define FILE_ReadWriteInfo   0x0941;  // 文件读写指令信息
#define DOCU_EXPORT_DELETE   0x0942;  // 文件管理导出和删除指令
#define FILE_ReadWriteResult 0x0943;  // 文件读写指令结果

#define SPCO_SYNC2DSP  0X094E  // 暂存数据同步到DSP, 非实时, 写
#define SPCO_HARDEXIST 0X094F  // 查询工业安全参数硬件是否存在, 非实时, 读

#define SPCO_PASSWORD     0X0950  // 工业安全认证密码
#define SPCO_STOPCONF     0X0951  // 停机配置
#define SPCO_SAFELOWSPEED 0X0952  // 安全低速配置

#define SPCO_IOINPUT  0X0953  // 安全IO DI
#define SPCO_IOOUTPUT 0X0954  // 安全IO DO

#define SPCO_APOSWAY   0X0955  // 轴极限生效方式
#define SPCO_AVELWAY   0X0956  // 轴速度生效方式
#define SPCO_APOS_PARA 0X0957  // 轴极限配置
#define SPCO_AVEL_PARA 0X0958  // 轴速度配置

#define SPCO_CVELWAY   0X0959  // 笛卡尔速度生效方式
#define SPCO_CPOSWAY   0X095A  // 笛卡尔位置生效方式
#define SPCO_CVEL_PARA 0X095B  // 笛卡尔速度配置

#define SPCO_IZONESTATUS    0X095C  // 工业安全_干涉区状态
#define SPCO_ITOOLSTATUS    0X095D  // 工业安全_末端监测对象状态
#define SPCO_IZONEPARA      0X095E  // 工业安全_干涉区配置
#define SPCO_IZONEWOBJ      0X095F  // 工业安全_干涉区工件参数
#define SPCO_ITOOLPARA      0X0960  // 工业安全_末端监测对象配置
#define SPCO_ITOOLMTCP_TOOL 0X0961  // 工业安全_末端监测对象MTCP工具参数

#define SPCO_CHECKYES     0X0962  // 工业安全_EEPROM同步
#define SPCO_SYSTEM_READY 0X0963  // 工业安全_芯片握手同步

#define SPCO_SAFEIO_REALTIME 0X0964  // 工业安全_安全IO 实时读取状态

#define SPCO_TOOLPARA     0X0965  // 工业安全_安全工具
#define SPCO_WOBJPARA     0X0966  // 工业安全_安全工件
#define SPCO_SAFETOOLMODE 0X0967  // 工业安全_安全工具模式

#define SPCO_SAFETOOLMODE_FIXCHECK 0X0970  // 工业安全_固定模式
#define SPCO_SAFEPARA_VER          0X0971  // 工业安全_硬件版本
#define SPCO_SAFEIO_DITRIGGER      0X0972  // 工业安全_DI阈值

#define SPCO_SAFEPARA_RESET_STATUS 0X097E  // 工业安全_重置状态
#define SPCO_SAFEPARA_RESET        0X097F  // 工业安全_重置

#ifdef COBOT
    #define SPCO_SPEED_REDUCING        0X0C0B  // 工业安全_缩减等级
    #define SPCO_SEND_INTERZONE_STATUS 0X0C0C  // 工业安全_干涉区参数下发状态

    #define SPCO_ATORQUE_WAY           0X0981  // 工业安全_关节转矩生效方式
    #define SPCO_ATORQUE_PARA          0X0982  // 工业安全_关节转矩参数
    #define SPCO_APOWER_WAY            0X0983  // 工业安全_关节功率生效方式
    #define SPCO_APOWER_PARA           0X0984  // 工业安全_关节功率参数
    #define SPCO_TCP_FORCE             0X0985  // 工业安全_TCP力
    #define SPCO_STATIC_MONITOR_WAY    0X0986  // 工业安全_安全静止监控生效方式
    #define SPCO_STATIC_MONITOR_PARA   0X0987  // 工业安全_安全静止监控参数
    #define SPCO_HOMING                0X0988  // 工业安全_安全原点
    #define SPCO_BODY_POWER            0X0989  // 工业安全_整机功率
    #define SPCO_BODY_MOMENTUM         0X098A  // 工业安全_整机动量
    #define SPCO_TCP_DIRECTION_WAY     0X098B  // 工业安全_TCP方向生效方式
    #define SPCO_TCP_DIRECTION         0X098C  // 工业安全_TCP方向
    #define SPCO_STOP_TIME             0X098D  // 工业安全_停机时间
    #define SPCO_STOP_DISTANCE         0X098E  // 工业安全_停机距离
    #define SPCO_STOP_TOLERANCE        0X098F  // 工业安全_停机容差
    #define SPCO_REDUCEMODE_APOS       0X0990  // 工业安全_缩减模式轴位置
    #define SPCO_REDUCEMODE_AVEL       0X0991  // 工业安全_缩减模式轴速度
    #define SPCO_REDUCEMODE_CVEL       0X0992  // 工业安全_缩减模式笛卡尔速度
    #define SPCO_ELBOW_SWITCH          0X0993  // 工业安全_肘部检测
    #define SPCO_POSITIONDISMATCH_PARA 0X0994  // 工业安全_位置不匹配参数
    #define SPCO_POSITIONDISMATCH_WAY  0X0995  // 工业安全_位置不匹配生效方式
    #define SPCO_DRAGTEACH_PARA        0X0996  // 工业安全_拖动示教
    #define SPCO_SAFETYMONITOR_SWITCH  0X0997  // 工业安全_一键开启关闭安全监控
#endif                                         // COBOT

#define SEND_WORKSTATION_TYPE 0X0980  // 上位机工作站模式

// 安全IO动作
#define CUSTOM_ACTION_JSON_UPDATE 0x030C;  // 更新安全IO动作JSON文件
#define CUSTOM_ACTION_EXEC        0x030D;  // 执行安全IO动作

#define CANOPEN_SDO_DEBUG       0x0A00;  // Canopen SDO调试
#define CANOPEN_NODE_MONITOR    0x0A01;  // Canopen 节点监控
#define CANOPEN_NODE_NMT        0x0A02;  // Canopen 节点NMT命令
#define CANOPEN_JSONFILE_CHANGE 0x0A03;  // Canopen 节点监控
#define CANOPEN_MASTER_STOP     0x0A04;  // Canopen主站停止（写）
#define CANOPEN_MASTER_STATE    0x0A05;  // Canopen主站状态（读）
#define CANOPEN_EMCY_ERROR      0x0A06;  // Canopen紧急报文错误信息（读）
#define CANOPEN_SDO_CFG_ERROR   0x0A07;  // Canopen SDO配置错误信息（读）

#define CONTROL_AUTHORITY_RMT_IO_SUB_MODE 0x0A08  // 远程IO单元控制权子模式
#define RUNLINE_RESET_MODE                0x0A09  // 行号重置策略(仅作用于远程IO单元控制权下)
#define CTRL_AUTHORITY_STOP_ENABLE_STATE  0x0A0A  // 停止使能策略(仅作用于远程IO单元控制权下)

#define DEVICENET_NODE_STATE          0x0A20;  // DeviceNet节点状态（读）
#define DEVICENET_JSONFILE_CHANGE     0x0A21;  // DeviceNet文件更新
#define DEVICENET_SCAN                0x0A22;  // DeviceNet扫描
#define DEVICENET_MASTER_STOP         0x0A23;  // DeviceNet主站停止（写）
#define DEVICENET_MASTER_STATE        0x0A24;  // DeviceNet主站状态（读）
#define NETWORK_FIELDBUS_UPLOAD       0x0A25;  // 网络组态上载（读）
#define NETWORK_FIELDBUS_DOWNLOAD     0x0A26;  // 网络组态下载（写）
#define NETWORK_FIELDBUS_IMPORT       0x0A27;  // 导入组态配置通知（写）
#define WRITE_ECATSLAVE_MANAGE_STATE  0x0A28;  // 写入Ecat从站管理状态（写）
#define READ_ECATSLAVE_MANAGE_STATE   0x0A29;  // 读取Ecat从站管理状态（读）
#define WRITE_ECATSLAVE_MANAGE_SWITCH 0x0A2A;  // 写入Ecat从站管理状态功能是否开启（写）
#define REFRESH_ECATSLAVE_STATE       0x0A2B;  // 刷新Ecat从站状态（写）

#define ECAT_ANALYSIS_FILE        0x0B00;  // EtherCAT组态文件解析
#define ETHERCAT_ADDA_STATE_READ  0x0B01;  // 读取DA/AD状态
#define ETHERCAT_ADDA_STATE_WRITE 0x0B02;  // 设置DA输出状态

#define MAIN_SPRING_PROPERTY 0x0B11;  // 平衡缸弹簧阈值与属性（读、写）
#define MAIN_SPRING_SET      0x0B12;  // 平衡缸弹簧维保（写）
#define MAIN_SPRING_DATA_GET 0x0B13;  // 获取平衡缸弹簧维保数据（读）

#define COBOT_BODY_POWER_STATE       0x0C00  // 设置机器人本体上下电状态
#define SET_COBOT_WIFI_PASSWORD      0x0C01  // 设置wifi密码
#define GRIPPER_THREE_POSITION_STATE 0x0C02  // 设置夹持器三位置使能状态

#define COBOT_ADDAWRITE 0x0C03  // 写入DA/AD信息

#define WRITE_TOOL_IO_SETTING                          0x0C05  // 写入末端io配置
#define NOTIFY_CONTROLLER_STRAT_TOOL_IO_CONFIG_MONITOR 0x0C06  // 控制器开启/关闭末端IO监控
#define COBOT_ABZ_VALUE                                0x0C07  // 协作 获取编码器数值
#define GET_TOOL_IO_VERSION_INFO                       0x0C08  // 协作 获取末端IO版本号
#define TOOL_IO_REUSE_MODEL                            0x0C09  // 协作 读/写末端复用模式 485/AD
#define RC_RS485_SWITCH_STATE                          0X0C10  // 协作 读/写电柜485开关状态

#define SINGLE_CONTROLLER_RUN_MODE           0x0C11  // 协作 读/写单电柜运行模式状态
#define GET_SINGLE_CONTROLLER_RUN_MODE_STATE 0x0C12  // 协作 获取设置单电柜运行模式的结果

#define SET_COBOT_WIFI_FREQUENCY_BAND 0x0C13  // 协作 设置电柜WiFi频段
#define GET_COBOT_WIFI_INFO           0x0C14  // 协作 获取电柜WiFi信息

#define GET_FIRST_BOOT_STATUS         0x0C1B  // 协作 获取电柜是否是第一次刷机后重启状态
#define GET_DRAG_TEACH_STATUS         0x0C1C  // 协作 获取拖动示教状态

#define ETHERNETIP_SCAN             0x8060;  // EthernetIP设备扫描
#define WRITE_EIPSLAVE_MANAGE_STATE 0x8061;  // 写入EIP从站管理状态（写）
#define READ_EIPSLAVE_MANAGE_STATE  0x8062;  // 读取EIP从站管理状态（读）
#define ETHERNETIP_CONN_STATE       0x8063;  // EthernetIP连接状态（读）
#define CONTROLLER_OPERATION_VALID  0x8064;  // 询问控制器指定的操作类型是否被允许（读）

#define MAINTENANCE_THRESHOLD_SET 0x8080;  // 设置维保阈值（写）
#define MAINTENANCE_TIME_SET      0x8081;  // 设置维保时间（写）
#define MAINTENANCE_DATA_GET      0x8082;  // 获取维保信息（读）
#define MAINTENANCE_DATA_CLEAR    0x8083;  // 清空所有维保数据（写）
#define MAINTENANCE_BACKUP        0x8084;  // PC维保数据备份加载（写）
#define MAINTENANCE_TP_BACKUP     0x8085;  // TP维保数据备份加载（写）
#define DEVICE_LIFE_CONFIG        0x8086;  // 设备寿命配置（读写）（减速机和丝杆）
#define DEVICE_DATA_COLLECT       0x8087;  // 设备数据采集（启停）（减速机和丝杆）
#define DEVICE_LIFE_RESULT        0x8088;  // 设备寿命结果获取（减速机和丝杆）
#define DEVICE_LIFEDATA_RESET     0x8089;  // 设备寿命数据重置（减速机和丝杆）
#define DEVICE_ROBOT_SUPPORT      0x808A;  // 本机型是否支持标志（减速机和丝杆）

#define DRAGTEACH_AUTORECORDPOINT_RESULT 0X0C1A  // 拖动示教记点结果反馈(协作)

// 调点功能优化
#define HOT_MODRPOS 0x0D01;  // 调试/自动/任意控制权下修改点

// 摩擦辨识
#define FRIC_IDENTIFY_GET_TRAJPOINT     0x0D31  // 获取控制器根据算法计算得到的推荐轨迹点值
#define START_FRIC_IDENTIFY             0x0D32  // 开始摩擦辨识
#define END_FRIC_IDENTIFY               0x0D33  // 终止摩擦辨识
#define READ_FRIC_IDENTIFY_RESULT       0x0D34  // 获取摩擦辨识结果
#define APPLY_FRIC_IDENTIFY_RESULT      0x0D35  // 应用摩擦辨识结果

#define SET_FRIC_COMPENSATION_STATUS    0x0D37  // 设置摩擦补偿状态
#define READ_COULOM_FRIC_PARAMS         0x0D38  // 获取库伦摩擦参数
#define SET_FRIC_IDENTIFY_TRAJ_VEL      0x0D39  // 设置摩擦辨识轨迹速度
#define RESTORE_FRIC_IDENTIFY_PARAM     0x0D3A  // 恢复出厂设置

// 间隙辨识
#define START_BACKLASH_IDENTIFY             0x0D42  // 开始间隙辨识
#define END_BACKLASH_IDENTIFY               0x0D43  // 终止间隙辨识
#define READ_BACKLASH_IDENTIFY_RESULT       0x0D44  // 获取间隙辨识结果
#define READ_BACKLASH_COMPENSATION_STATUS   0x0D46  // 获取间隙补偿开关状态
#define SET_BACKLASH_COMPENSATION_STATUS    0x0D47  // 设置间隙补偿开关状态
#define READ_COULOM_BACKLASH_PARAMS         0x0D48  // 获取间隙参数
#define SET_BACKLASH_IDENTIFY_TRAJ_VEL      0x0D49  // 设置间隙辨识轨迹速度
#define RESTORE_BACKLASH_IDENTIFY_PARAM     0x0D4A  // 恢复出厂设置

#define PLUGIN_TEXT_WRITE   0xFF00  // 插件WRITE文本
#define PLUGIN_TEXT_READ    0xFF01  // 插件READ文本
#define PLUGIN_BINARY_WRITE 0xFF02  // 插件WRITE二进制
#define PLUGIN_BINARY_READ  0xFF03  // 插件READ二进制
