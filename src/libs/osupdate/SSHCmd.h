#pragma once
#include "string.h"
struct SSHCfg {
    char localfile[512];
    char scppath[128];
    char hostname[32];
    char username[32];
    char password[32];
    char cmdline[512];
};
enum E_SSH_SendFileStatus//文件传输状态
{
    SSH_StatusEstablish = 0,
    SSH_StatusTransmit,
    SSH_StatusFinish,
    SSH_StatusShRunning,
    SSH_StatusUpdateSuccess,
    SSH_StatusAbort,
    SSH_StatusTimeout,
    SSH_StatusError,
};
struct SSHSendFileStatus {
    int status;
    int progress; // 进度  
    int errorCode; // 错误码  
};
/*
* int ssh2cmd_with_timeout(SSHCfg* cfg, char* retbuff, int size, int timeout)
* When checking the progress of polling, there is a timeout time limit for polling. 
* This function needs to be used to adjust the timeout time to prevent it from lagging
* for too long in the SSHCMD function, which may cause the timeout time to be too long.
*/
int ssh2cmd_with_timeout(SSHCfg* cfg, char* retbuff, int size, double timeout);
int ssh2cmd_retry(SSHCfg* ssh_cfg, char* retbuff, int size, int retry_count);
int ssh2cmd(SSHCfg* cfg, char* retbuff, int size);
int scp_write_retry(SSHCfg* ssh_cfg,int retry_count);
int scp_write(SSHCfg* cfg);