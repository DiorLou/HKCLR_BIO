#include "robotparameters.h"
#include <QDebug>
#include "communication.h"
#include "communicationengine.h"

#include "InoRobBusiness/RobotParam/IRobotParam.h"
// #include "robotioinfo.h"
// #include "instance.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "InoRobBusiness/Controller/Resource/ResourceDefault.h"
#include "IController.h"
#include "cobotlogex.h"
#include "modulesutils.h"

#ifdef INOCOBOTTP_MSVC_QT5
static QList<double> gLastCompensationParameters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#else
static QList<double> gLastCompensationParameters = QList<double>(16, 0);
#endif


double *qListToArrary(const QList<double> &list)
{
    int size = list.size();
    double *ans = new double[size];
    for (int i = 0; i < size; ++i) {
        ans[i] = list[i];
    }
    return ans;
}

QList<double> arraryToQList(double data[], int size)
{
    QList<double> ans;
    for (int i = 0; i < size; ++i) {
        ans.push_back(data[i]);
    }
    return ans;
}

InoRobBusiness::IRobotArm *RobotParameters::robotArm()
{
    return _IRobotArm;
}

void RobotParameters::setRobotParamsForSimulation(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<double> structParams;
    int ret1 = _IRobotArm->getCoRotbotStructParameters(structParams);
    foreach (double a, structParams) {
        qDebug() << "structParams" << a;
    }
    if (ret1 == ERROR_OK) {
        emit CommunicationEngine::instance()->signal_getRobotParametersForSimulation(
            absCmd->m_object,
            QList<double>(structParams.begin(), structParams.end()));
        // PRINT_MSG(QObject::tr("Update Robot struct parameters for simulation success!"));
    } else
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to update robot parameters for simulation model."));

    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::readRobotName(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    char robotStructName[128] = {0};
    bool ret = _IMonitor->GetRobotName(robotStructName);
    QString name;
    if (ret)
        name = robotStructName;
    else
        name = "Unknown";

    emit CommunicationEngine::instance()->singnal_readRobotName_result(
        absCmd->m_object, ret, name);

    FREQ_LOG_PRINT_TIMESTAMP
}


void RobotParameters::getRobotParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<double> structParams;
    double reduRatio[AXIS_NUMB] = {};
    double compParam[COM_PARM_NUM] = {};
    double coupParaM[AXIS_NUMB] = {}, coupParaS[AXIS_NUMB] = {};
    int ret1 = _IRobotArm->getCoRotbotStructParameters(structParams);
    int ret2 = _IRobotArm->getReductionRatioParam(reduRatio);
    int ret3 = _IRobotArm->getRobotCompParam(compParam);
    if (ret3 == ERROR_OK) {
        gLastCompensationParameters.clear();
        for (int i = 0; i < COM_PARM_NUM; ++i) {
            gLastCompensationParameters << compParam[i];
        }
    } else {
        for (int i = 0; i < COM_PARM_NUM; ++i) {
            gLastCompensationParameters << 0;
        }
    }
    // int ret4 = _IRobotParam->getCouplingParam(coupParaM, coupParaS);
    InoRobBusiness::IRobotParamRange *param = comm()->robotParam()->getRobotParamRange();

    QList<double> structMax, stuctMin, reduRadioMax, reduRadioMin, comMax, comMin, coupleMax, coupleMin;

    vector<std::string> sixStructName = {"a1(mm)", "a2(mm)", "a3(mm)", "d3(mm)", "d4(mm)", "df(mm)", "d1(mm)", "d5(mm)", "d6(mm)"};
    std::string keyName = "StructParam";
    for (const std::string &i : sixStructName) {
        stuctMin.push_back(param->getDoubleMinValue(keyName, i));
        structMax.push_back(param->getDoubleMaxValue(keyName, i));
    }

    vector<std::string> sixJointName = {"J1", "J2", "J3", "J4", "J5", "J6"};
    vector<std::string> names;
    // 减速比
    std::string paraStructName = "ReductionRatio";
    for (const std::string &i : sixJointName) {
        reduRadioMin.push_back(param->getDoubleMinValue(paraStructName, i));
        reduRadioMax.push_back(param->getDoubleMaxValue(paraStructName, i));
    }
    // 补偿参数
    std::string unit = "(°)";
    paraStructName = "InternalCompensation";
    for (int i = 0; i < sixJointName.size(); ++i) {
        sixJointName[i] = sixJointName[i] + unit;
    }
    sixJointName.push_back("d3(mm)");
    sixJointName.push_back("d5(mm)");
    sixJointName.push_back("a4(mm)");
    sixJointName.push_back("a5(mm)");
    sixJointName.push_back("J7(°)");
    for (const std::string &i : sixJointName) {
        comMin.push_back(param->getDoubleMinValue(paraStructName, i));
        comMax.push_back(param->getDoubleMaxValue(paraStructName, i));
    }
    // 耦合参数
    //  获取范围
    //  paraStructName = "CouplingParam";
    //  std::string paraName = "J5(分子)";//机型参数查询 必须写中文
    //  coupleMin << param->getDoubleMinValue(paraStructName, paraName);
    //  coupleMax << param->getDoubleMaxValue(paraStructName, paraName);

    // paraName = "J6(分母)";//机型参数查询 必须写中文
    // coupleMin << param->getDoubleMinValue(paraStructName, paraName);
    // coupleMax << param->getDoubleMaxValue(paraStructName, paraName);

    // 机器人型号 2
    char robotStructName[128] = {0};
    bool ret5 = _IMonitor->GetRobotName(robotStructName);
    QString name;
    if (ret5)
        name = robotStructName;
    else
        name = "Unknown";

    if (ret1 == ERROR_OK && ret2 == ERROR_OK
        && ret3 == ERROR_OK /*&& ret4 == ERROR_OK*/) {
        QList<double> compen = arraryToQList(compParam, COM_PARM_NUM);
        double beta3 = compParam[13];
        compParam[13] = compen[10];
        compen[10] = beta3;
        emit CommunicationEngine::instance()->signal_getRobotParameters_result(
            absCmd->m_object,
            name,
            QList<double>(structParams.begin(), structParams.end()),
            stuctMin,
            structMax,
            arraryToQList(reduRatio, AXIS_NUMB),
            reduRadioMin,
            reduRadioMax,
            compen,
            comMin,
            comMax,
            QList<double>() << coupParaM[4] << coupParaS[5],
            coupleMin,
            coupleMax);
    } else {
        emit CommunicationEngine::instance()->signal_getRobotParameters_isSuccess(
            absCmd->m_object, false);
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            QObject::tr("Failed to get robot parameters."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    // int ret4 = _IRobotParam->getRotbotStructParameters(structParams);
}

void RobotParameters::setRobotParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [structParams, reduRatioParam, compParam, coupling] = ((CmdDatas<QList<double>, QList<double>, QList<double>, QList<double>> *)absCmd)->m_data;
    std::vector<double> vector;
    std::copy(structParams.begin(), structParams.end(), std::back_inserter(vector));
    for (int i = reduRatioParam.size(); i < AXIS_NUMB; ++i)
        reduRatioParam.push_back(0);

    for (int i = compParam.size(); i < COM_PARM_NUM; ++i)
        compParam.push_back(0);

    double beta3 = compParam[10];
    for (int i = 10; i < 16; ++i) {
        compParam[i] = gLastCompensationParameters.at(i);
    }
    compParam[13] = beta3;
    // qDebug()<<__FUNCTION__<<compParam;

    bool check = InoRobBusiness::StatusChecks::getInstance().cobotCheck(
        InoRobBusiness::StatusItemGroup::CTRL_AUTHORITY_TEACHPAD
        | InoRobBusiness::StatusItemGroup::DEVICE_MODE_MANUAL_LOW
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_DISENABLE);
    if (!check) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("Save failed. Please switch to manual low mode, disable the robot, and change control authority to the teach pendant, and then try again."));
        return;
    }

    int ret1 = _IRobotArm->saveCoRobotStructParam(vector, false);
    int ret2 = _IRobotArm->saveRobotReductionRatioParam(&reduRatioParam[0], false);
    int ret3 = _IRobotArm->saveRobotCompensationParam(&compParam[0], false);
    // int ret4 = _IRobotParam->getCouplingParam(coupParaM, coupParaS);
    // if(ret4 == ERROR_OK){
    //     QList<double> temp;
    //     for(int i=0;i<AXIS_NUMB;++i){
    //         temp.push_back(coupParaM[i]);
    //     }
    //     for(int i=0;i<AXIS_NUMB;++i){
    //         temp.push_back(coupParaS[i]);
    //     }
    //     temp[4] = coupling[0];
    //     temp[AXIS_NUMB + 5] = coupling[1];
    //     ret4 = _IRobotParam->saveRobotCouplingParam(&temp[0], false);
    // }
    // coupling
    QString error;
    if (ret1 != ERROR_OK) {
        error += QObject::tr("Failed to save robot structal parameters. ") + "\n";
    }
    if (ret2 != ERROR_OK) {
        error += QObject::tr("Failed to save robot reduction parameters.") + "\n";
    }
    if (ret3 != ERROR_OK) {
        error += QObject::tr("Failed to save robot internal compensation parameters.");
    }
    // if(ret4 != ERROR_OK){
    //     error += QObject::tr("Save robot coupling compensation parameters falid!");
    // }
    if (!error.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    }
    if (ret1 == ERROR_OK && ret2 == ERROR_OK && ret3 == ERROR_OK){
        PRINT_MSG(QObject::tr("Robot parameters sent successfully."));
    }

    if (ret1 == ERROR_OK || ret2 == ERROR_OK || ret3 == ERROR_OK /*&& ret4 != ERROR_OK*/) {
        bool ok = true;

        _IRobotArm->saveFileCommond(&ok);
        if (ok) {
            PRINT_WARN(RobotParametersTr::tr("After modifying the structure and kinematic parameters of the robot, please power it on again and set the zero point!"));
            setRobotParamsForSimulation(absCmd);
        }
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::getTeachParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    QList<double> posVelRangeMin;
    QList<double> posVelRangeMax;

    QList<double> jointVelRangeMin;
    QList<double> jointVelRangeMax;

    QList<double> posAccRangeMin;
    QList<double> posAccRangeMax;

    QList<double> jointAccRangeMin;
    QList<double> jointAccRangeMax;

    // 最大允许位置速度（示教）
    double posSpeed = 0.0;
    int retPSpeed = _IRobotArm->readTeachCoorMaxSpeed(posSpeed);

    // 最大允许姿态速度（示教）
    double guiseSpeed = 0.0;
    int retGSpeed = _IRobotArm->readTeachMaxGuiseSpeed(guiseSpeed);

    // 最大允许关节速度（示教）
    double jSpeedParam[AXIS_NUM] = {0.0};
    int retJSpeed = _IRobotArm->getTeachAxisMaxSpeed(jSpeedParam);

    // 最大允许位置加速度（示教）
    double posAcc = 0.0;
    int retPAcc = _IRobotArm->readTeachCoorMaxAcc(posAcc);

    // 最大允许姿态加速度（示教）
    double guiseAcc = 0.0;
    int retGAcc = _IRobotArm->readTeachMaxGuiseAcc(guiseAcc);

    // 最大允许关节加速度（示教）
    double jAccParam[AXIS_NUMB] = {0.0};
    int retJAcc = _IRobotArm->getTeachAxisMaxAcc(jAccParam);

    InoRobBusiness::IRobotParamRange *param = comm()->robotParam()->getRobotParamRange();

    getParamRangeDoubleValue(param, "TeachVelocityParam", "coorMaxSpeed(mm/s)",
                             posVelRangeMin, posVelRangeMax);
    getParamRangeDoubleValue(param, "TeachVelocityParam", "guiseMaxSpeed(°/s)",
                             posVelRangeMin, posVelRangeMax);

    vector<std::string> paraVelNames = {"J1(°/s)", "J2(°/s)", "J3(°/s)",
                                        "J4(°/s)", "J5(°/s)", "J6(°/s)"};
    getParamRangeDoubleValue(param, "TeachVelocityParam", paraVelNames,
                             jointVelRangeMin, jointVelRangeMax);

    getParamRangeDoubleValue(param, "TeachAccParam", "coorMaxAcc(mm/s²)",
                             posAccRangeMin, posAccRangeMax);
    getParamRangeDoubleValue(param, "TeachAccParam", "guiseMaxAcc(°/s²)",
                             posAccRangeMin, posAccRangeMax);

    paraVelNames.clear();
    paraVelNames = {"J1(°/s²)", "J2(°/s²)", "J3(°/s²)",
                    "J4(°/s²)", "J5(°/s²)", "J6(°/s²)"};
    getParamRangeDoubleValue(param, "TeachAccParam", paraVelNames,
                             jointAccRangeMin, jointAccRangeMax);

    if (retPSpeed == ERROR_OK && retGSpeed == ERROR_OK && retJSpeed == ERROR_OK
        && retPAcc == ERROR_OK && retGAcc == ERROR_OK && retJAcc == ERROR_OK) {
        emit CommunicationEngine::instance()->signal_getTeachParameters_result(
            absCmd->m_object,
            QList<double>() << posSpeed << guiseSpeed,
            posVelRangeMin,
            posVelRangeMax,
            arraryToQList(jSpeedParam, AXIS_NUM),
            jointVelRangeMin,
            jointVelRangeMax,
            QList<double>() << posAcc << guiseAcc,
            posAccRangeMin,
            posAccRangeMax,
            arraryToQList(jAccParam, AXIS_NUMB),
            jointAccRangeMin,
            jointAccRangeMax);
    } else {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            QObject::tr("Failed to get teach parameters."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::setTeachParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool check = InoRobBusiness::StatusChecks::getInstance().cobotCheck(
        InoRobBusiness::StatusItemGroup::CTRL_AUTHORITY_TEACHPAD
        | InoRobBusiness::StatusItemGroup::DEVICE_MODE_MANUAL_LOW
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_DISENABLE);
    if (!check) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("Save failed. Please switch to manual low mode, disable the robot, and change control authority to the teach pendant, and then try again."));
        return;
    }

    if (!_IRobotArm->checkFileSaveFlag()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("System busy, please try again later."));
        return;
    }

    auto [posVelParams, jointVelParams, posAccParams, jointAccParams] = ((CmdDatas<QList<double>, QList<double>, QList<double>, QList<double>> *)absCmd)->m_data;

    int retPSpeed = _IRobotArm->writeTeachCoorMaxSpeed(posVelParams.at(0));
    int retGSpeed = _IRobotArm->writeTeachMaxGuiseSpeed(posVelParams.at(1));

    double jSpeedParam[AXIS_NUM] = {0.0};
    for (int i = 0; i < jointVelParams.count(); i++) {
        jSpeedParam[i] = jointVelParams.at(i);
    }

    int retJSpeed = _IRobotArm->saveTeachAxisMaxSpeed(jSpeedParam);

    int retPAcc = _IRobotArm->writeTeachCoorMaxAcc(posAccParams.at(0));
    int retGAcc = _IRobotArm->writeTeachMaxGuiseAcc(posAccParams.at(1));

    double jAccParam[AXIS_NUMB] = {0.0};
    for (int i = 0; i < jointAccParams.count(); i++) {
        jAccParam[i] = jointAccParams.at(i);
    }

    int retJAcc = _IRobotArm->saveTeachAxisMaxAcc(jAccParam);

    QString error;
    if (retPSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable position velocity.") + "\n";
    }
    if (retGSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable orientation velocity.") + "\n";
    }
    if (retJSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable joint velocity.") + "\n";
    }
    if (retPAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable position acceleration.") + "\n";
    }
    if (retGAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable orientation acceleration.") + "\n";
    }
    if (retJAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable joint acceleration.");
    }
    if (!error.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    }
    if (retPSpeed == ERROR_OK && retGSpeed == ERROR_OK && retJSpeed == ERROR_OK
        && retPAcc == ERROR_OK && retGAcc == ERROR_OK && retJAcc == ERROR_OK) {
        bool isOK = true;
        _IRobotArm->saveFileCommond(&isOK);
        if (isOK) {
            PRINT_MSG(QObject::tr("Teach parameters save successfully."));
        } else {
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                QObject::tr("Failed to save teach parameters."));
        }
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::getMotionParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    QList<double> posVelRangeMin;
    QList<double> posVelRangeMax;

    QList<double> jointVelRangeMin;
    QList<double> jointVelRangeMax;

    QList<double> posAccRangeMin;
    QList<double> posAccRangeMax;

    QList<double> jointAccRangeMin;
    QList<double> jointAccRangeMax;

    QList<double> posDecRangeMin;
    QList<double> posDecRangeMax;

    QList<double> jointDecRangeMin;
    QList<double> jointDecRangeMax;

    QList<double> transRangeMin;
    QList<double> transRangeMax;

    // 最大允许位置速度（示教）
    double posSpeed = 0.0;
    int retPSpeed = _IRobotArm->readCoorMaxSpeed(posSpeed);

    // 最大允许姿态速度（示教）
    double guiseSpeed = 0.0;
    int retGSpeed = _IRobotArm->readMaxGuiseSpeed(guiseSpeed);

    // 最大允许关节速度（运动）
    double jSpeedParam[AXIS_NUM] = {0.0};
    int retJSpeed = _IRobotArm->getAxisMaxSpeed(jSpeedParam);

    // 最大允许位置加速度（运动）
    double posAcc = 0.0;
    int retPAcc = _IRobotArm->readCoorMaxAcc(posAcc);

    // 最大允许姿态加速度（运动）
    double guiseAcc = 0.0;
    int retGAcc = _IRobotArm->readMaxGuiseAcc(guiseAcc);

    // 最大允许关节加速度（运动）
    double jAccParam[AXIS_NUMB] = {0.0};
    int retJAcc = _IRobotArm->getAxisMaxAcc(jAccParam);

    // 最大允许位置减速度（运动）
    double posDec = 0.0;
    int retPDec = _IRobotArm->readCoorMaxDec(posDec);

    // 最大允许姿态减速度（运动）
    double guiseDec = 0.0;
    int retGDec = _IRobotArm->readGuiseMaxDec(guiseDec);

    // 最大允许关节减速度（运动）
    double jDecParam[AXIS_NUMB] = {0.0};
    int retJDec = _IRobotArm->getAxisMaxDec(jDecParam);

    // 过渡特性（运动）
    double jointTransUnit = 0.0;
    double posTransUnit = 0.0;
    double angleTransUnit = 0.0;
    int retTrans = _IRobotArm->readTransJogDistan(jointTransUnit, posTransUnit, angleTransUnit);

    InoRobBusiness::IRobotParamRange *param = comm()->robotParam()->getRobotParamRange();

    getParamRangeDoubleValue(param, "RunVelocityParam", "coorMaxSpeed(mm/s)",
                             posVelRangeMin, posVelRangeMax);
    getParamRangeDoubleValue(param, "RunVelocityParam", "guiseMaxSpeed(°/s)",
                             posVelRangeMin, posVelRangeMax);

    vector<std::string> paraVelNames = {"J1(°/s)", "J2(°/s)", "J3(°/s)",
                                        "J4(°/s)", "J5(°/s)", "J6(°/s)"};
    getParamRangeDoubleValue(param, "RunVelocityParam", paraVelNames,
                             jointVelRangeMin, jointVelRangeMax);

    getParamRangeDoubleValue(param, "RunAccParam", "coorMaxAcc(mm/s²)",
                             posAccRangeMin, posAccRangeMax);
    getParamRangeDoubleValue(param, "RunAccParam", "guiseMaxAcc(°/s²)",
                             posAccRangeMin, posAccRangeMax);
    paraVelNames.clear();
    paraVelNames = {"J1(°/s²)", "J2(°/s²)", "J3(°/s²)",
                    "J4(°/s²)", "J5(°/s²)", "J6(°/s²)"};
    getParamRangeDoubleValue(param, "RunAccParam", paraVelNames,
                             jointAccRangeMin, jointAccRangeMax);

    getParamRangeDoubleValue(param, "RunDecreaseAccParam", "coorMaxDec(mm/s²)",
                             posDecRangeMin, posDecRangeMax);
    getParamRangeDoubleValue(param, "RunDecreaseAccParam", "guiseMaxDec(°/s²)",
                             posDecRangeMin, posDecRangeMax);
    getParamRangeDoubleValue(param, "RunDecreaseAccParam", paraVelNames,
                             jointDecRangeMin, jointDecRangeMax);

    getParamRangeDoubleValue(param, "RunTransitionParam", "jointTrans",
                             transRangeMin, transRangeMax);
    getParamRangeDoubleValue(param, "RunTransitionParam", "posTrans",
                             transRangeMin, transRangeMax);

    if (retPSpeed == ERROR_OK && retGSpeed == ERROR_OK && retJSpeed == ERROR_OK
        && retPAcc == ERROR_OK && retGAcc == ERROR_OK && retJAcc == ERROR_OK
        && retPDec == ERROR_OK && retGDec == ERROR_OK && retJDec == ERROR_OK
        && retTrans == ERROR_OK) {
        emit CommunicationEngine::instance()->signal_getMotionParameters_result(
            absCmd->m_object,
            QList<double>() << posSpeed << guiseSpeed,
            posVelRangeMin,
            posVelRangeMax,
            arraryToQList(jSpeedParam, AXIS_NUM),
            jointVelRangeMin,
            jointVelRangeMax,
            QList<double>() << posAcc << guiseAcc,
            posAccRangeMin,
            posAccRangeMax,
            arraryToQList(jAccParam, AXIS_NUMB),
            jointAccRangeMin,
            jointAccRangeMax,
            QList<double>() << posDec << guiseDec,
            posDecRangeMin,
            posDecRangeMax,
            arraryToQList(jDecParam, AXIS_NUMB),
            jointDecRangeMin,
            jointDecRangeMax,
            QList<double>() << jointTransUnit << posTransUnit,
            transRangeMin,
            transRangeMax);
    } else {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            QObject::tr("Failed to get motion parameters."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::setMotionParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool check = InoRobBusiness::StatusChecks::getInstance().cobotCheck(
        InoRobBusiness::StatusItemGroup::CTRL_AUTHORITY_TEACHPAD
        | InoRobBusiness::StatusItemGroup::DEVICE_MODE_MANUAL_LOW
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_DISENABLE);
    if (!check) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("Save failed. Please switch to manual low mode, disable the robot, and change control authority to the teach pendant, and then try again."));
        return;
    }

    if (!_IRobotArm->checkFileSaveFlag()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("System busy, please try again later."));
        return;
    }

    auto [posVelParams, jointVelParams, posAccParams, jointAccParams, posDecParams, jointDecParams, transParams] = ((CmdDatas<QList<double>, QList<double>, QList<double>, QList<double>, QList<double>, QList<double>, QList<double>> *)absCmd)->m_data;

    int retPSpeed = _IRobotArm->writeCoorMaxSpeed(posVelParams.at(0));
    int retGSpeed = _IRobotArm->writeMaxGuiseSpeed(posVelParams.at(1));

    double jSpeedParam[AXIS_NUM] = {0.0};
    for (int i = 0; i < jointVelParams.count(); i++) {
        jSpeedParam[i] = jointVelParams.at(i);
    }

    int retJSpeed = _IRobotArm->saveAxisMaxSpeed(jSpeedParam);

    int retPAcc = _IRobotArm->writeCoorMaxAcc(posAccParams.at(0));
    int retGAcc = _IRobotArm->writeMaxGuiseAcc(posAccParams.at(1));

    double jAccParam[AXIS_NUMB] = {0.0};
    for (int i = 0; i < jointAccParams.count(); i++) {
        jAccParam[i] = jointAccParams.at(i);
    }

    int retJAcc = _IRobotArm->saveAxisMaxAcc(jAccParam);

    int retPDec = _IRobotArm->writeCoorMaxDec(posDecParams.at(0));
    int retGDec = _IRobotArm->writeGuiseMaxDec(posDecParams.at(1));

    double jDecParam[AXIS_NUMB] = {0.0};
    for (int i = 0; i < jointDecParams.count(); i++) {
        jDecParam[i] = jointDecParams.at(i);
    }

    int retJDec = _IRobotArm->saveAxisMaxDec(jDecParam);

    double angleTransUnit = 0.0;
    int retTrans = _IRobotArm->writeTransJogDistan(transParams.at(0), transParams.at(1), angleTransUnit);

    QString error;
    if (retPSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable position velocity.") + "\n";
    }
    if (retGSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable orientation velocity.") + "\n";
    }
    if (retJSpeed != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable joint velocity.") + "\n";
    }
    if (retPAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable position acceleration.") + "\n";
    }
    if (retGAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable orientation acceleration.") + "\n";
    }
    if (retJAcc != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable joint acceleration.") + "\n";
    }
    if (retPDec != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable position deleration.") + "\n";
    }
    if (retGDec != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable orientation deleration.") + "\n";
    }
    if (retJDec != ERROR_OK) {
        error += QObject::tr("Failed to save Maximum allowable joint deleration.") + "\n";
    }
    if (retTrans != ERROR_OK) {
        error += QObject::tr("Failed to save transition characteristic settings.");
    }
    if (!error.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    }
    if (retPSpeed == ERROR_OK && retGSpeed == ERROR_OK && retJSpeed == ERROR_OK
        && retPAcc == ERROR_OK && retGAcc == ERROR_OK && retJAcc == ERROR_OK
        && retPDec == ERROR_OK && retGDec == ERROR_OK && retJDec == ERROR_OK
        && retTrans == ERROR_OK) {
        bool isOK = true;
        _IRobotArm->saveFileCommond(&isOK);
        if (isOK) {
            PRINT_MSG(QObject::tr("Motion parameters sent successfully."));
        } else {
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                QObject::tr("Failed to save motion parameters."));
        }
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

int RobotParameters::RobotParamFileChange(const int &type)
{
    char robotStructName[128] = {0};
    bool ret = _IMonitor->GetRobotName(robotStructName);
    QString name;
    if (ret)
        name = robotStructName;
    else
        name = "Unknown";

    QJsonObject obj;
    obj["path"] = "RobotParams/MachineParams.json";
    obj["machine"] = name;
    obj["type"] = type;

    QJsonDocument doc(obj);
    QByteArray array = doc.toJson(QJsonDocument::Compact);
	
    char* info = new char[array.size() + 1];
    std::strcpy(info, array);
    qDebug() << "info = " << info;

    return _IControl->RobotParamFileChange(info);
}

int RobotParameters::RobotParamServoCurrent(QByteArray &info)
{
    std::string content;
    int ret = _IControl->RobotParamServoCurrent(content);

    size_t totalSize = content.size();
    size_t offset = 0;
    info.reserve(totalSize);

    while (offset < totalSize) {
        size_t chunkSize = qMin(static_cast<size_t>(4096), totalSize - offset);
        QByteArray chunk = QByteArray::fromRawData(content.data() + offset, chunkSize);
        info.append(chunk);
        offset += chunkSize;
    }
#ifndef INOCOBOTTP_MSVC_QT5
    qDebug() << "content = " << content;
    qDebug() << "totalSize = " << totalSize;
#endif
    return ret;
}

int RobotParameters::RobotParamServoStart(char *info)
{
    return _IControl->RobotParamServoStart(info);
}

int RobotParameters::RobotParamServoStop()
{
    return _IControl->RobotParamServoStop();
}

int RobotParameters::RobotParamUpdateStatusRead(QByteArray &info)
{
    std::string content;
    int ret = _IControl->RobotParamUpdateStatusRead(content);
    size_t totalSize = content.size();
    size_t offset = 0;
    info.reserve(totalSize);

    while (offset < totalSize) {
        size_t chunkSize = qMin(static_cast<size_t>(1024), totalSize - offset);
        QByteArray chunk = QByteArray::fromRawData(content.data() + offset, chunkSize);
        info.append(chunk);
        offset += chunkSize;
    }
    // qDebug() << "ret" << ret;
    // qDebug() << "info" << info;
    return ret;
}

void RobotParameters::getSevenRobotParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<double> structParams;
    double reduRatio[AXIS_NUMB] = {};
    double compParam[COM_PARM_NUM] = {};
    double coupParaM[AXIS_NUMB] = {}, coupParaS[AXIS_NUMB] = {};

    int ret1 = _IRobotArm->getSevenRobotStructParameters(structParams);
    int ret2 = _IRobotArm->getReductionRatioParam(reduRatio);
    int ret3 = _IRobotArm->getRobotCompParam(compParam);
    if (ret3 == ERROR_OK) {
        gLastCompensationParameters.clear();
        for (int i = 0; i < COM_PARM_NUM; ++i) {
            gLastCompensationParameters << compParam[i];
        }
    } else {
        for (int i = 0; i < COM_PARM_NUM; ++i) {
            gLastCompensationParameters << 0;
        }
    }
    InoRobBusiness::IRobotParamRange *param = comm()->robotParam()->getRobotParamRange();

    QList<double> structMax, stuctMin, reduRadioMax, reduRadioMin, comMax, comMin, coupleMax, coupleMin;

    vector<std::string> sixStructName = {"a1(mm)", "a2(mm)", "a3(mm)", "d3(mm)", "d4(mm)", "df(mm)", "d1(mm)", "d5(mm)", "d6(mm)"};

    std::string keyName = "StructParam";
    for (const std::string &i : sixStructName) {
        stuctMin.push_back(param->getDoubleMinValue(keyName, i));
        structMax.push_back(param->getDoubleMaxValue(keyName, i));
    }

    vector<std::string> sixJointName = {"J1", "J2", "J3", "J4", "J5", "J6"};
    vector<std::string> names;
    // 减速比
    std::string paraStructName = "ReductionRatio";
    for (const std::string &i : sixJointName) {
        reduRadioMin.push_back(param->getDoubleMinValue(paraStructName, i));
        reduRadioMax.push_back(param->getDoubleMaxValue(paraStructName, i));
    }

    // 补偿参数
    std::string unit = "(°)";
    paraStructName = "InternalCompensation";
    for (int i = 0; i < sixJointName.size(); ++i) {
        sixJointName[i] = sixJointName[i] + unit;
    }
    sixJointName.push_back("d3(mm)");
    sixJointName.push_back("d5(mm)");
    sixJointName.push_back("a4(mm)");
    sixJointName.push_back("a5(mm)");
    sixJointName.push_back("J7(°)");
    for (const std::string &i : sixJointName) {
        comMin.push_back(param->getDoubleMinValue(paraStructName, i));
        comMax.push_back(param->getDoubleMaxValue(paraStructName, i));
    }

    char robotStructName[128] = {0};
    bool ret5 = _IMonitor->GetRobotName(robotStructName);
    QString name;
    if (ret5)
        name = robotStructName;
    else
        name = "Unknown";

    if (ret2 == ERROR_OK && ret1 == ERROR_OK
        && ret3 == ERROR_OK) {
        qDebug() << "all Ok";
        QList<double> compen = arraryToQList(compParam, COM_PARM_NUM);
        double beta3 = compParam[13];
        compParam[13] = compen[10];
        compen[10] = beta3;
        emit CommunicationEngine::instance()->signal_getSevenRobotParameters_result(
            absCmd->m_object,
            name,
            QList<double>(structParams.begin(), structParams.end()),
            stuctMin,
            structMax,
            arraryToQList(reduRatio, AXIS_NUMB),
            reduRadioMin,
            reduRadioMax,
            compen,
            comMin,
            comMax);
        qDebug() << "emit OK";
    } else {
        emit CommunicationEngine::instance()->signal_getSevenRobotParameters_isSuccess(
            absCmd->m_object, false);
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            QObject::tr("Failed to get robot parameters."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::setSevenRobotParams(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        auto [structParams, reduRatioParam, coupling] = ((CmdDatas<QList<double>, QList<double>, QList<double>> *)absCmd)->m_data;
    std::vector<double> vector;
    std::copy(structParams.begin(), structParams.end(), std::back_inserter(vector));
    for (int i = reduRatioParam.size(); i < AXIS_NUMB; ++i)
        reduRatioParam.push_back(0);

    // qDebug()<<__FUNCTION__<<compParam;

    bool check = InoRobBusiness::StatusChecks::getInstance().cobotCheck(
        InoRobBusiness::StatusItemGroup::CTRL_AUTHORITY_TEACHPAD
        | InoRobBusiness::StatusItemGroup::DEVICE_MODE_MANUAL_LOW
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_DISENABLE);
    if (!check) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            RobotParametersTr::tr("Save failed. Please switch to manual low mode, disable the robot, and change control authority to the teach pendant, and then try again."));
        return;
    }

    int ret1 = _IRobotArm->saveSevenRobotStructParam(vector, false);
    int ret2 = _IRobotArm->saveRobotReductionRatioParam(&reduRatioParam[0], false);

    QString error;
    if (ret1 != ERROR_OK) {
        error += QObject::tr("Failed to save robot structal parameters. ") + "\n";
    }
    if (ret2 != ERROR_OK) {
        error += QObject::tr("Failed to save robot reduction parameters.") + "\n";
    }

    if (!error.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    }
    if (ret1 == ERROR_OK && ret2 == ERROR_OK /*&& ret3 == ERROR_OK*/){
        PRINT_MSG(QObject::tr("Robot parameters sent successfully."));
    }

    if (ret1 == ERROR_OK || ret2 == ERROR_OK /*|| ret3 == ERROR_OK*/ /*&& ret4 != ERROR_OK*/) {
        bool ok = true;

        _IRobotArm->saveFileCommond(&ok);
        if (ok) {
            PRINT_WARN(RobotParametersTr::tr("After modifying the structure and kinematic parameters of the robot, please power it on again and set the zero point!"));
            setRobotParamsForSimulation(absCmd);
        }
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotParameters::setSevenLoadMotionStatus(AbstractCmd *absCmd)
{
    // FREQ_LOG_PRINT_TIMESTAMP_THREAD
    // auto [status] = ((CmdDatas<int> *)absCmd)->m_data;
    // if(status == 1) {
    //     if (!Communication::instance()->IsEnable()) {
    //         PRINT_MSG(QObject::tr("Please enable the robot first."));
    //         return;
    //     }
    // }
    // int ret = _IRobotArm->setSevenLoadMotionStatus(status);

    // QString error;
    // if (ret != ERROR_OK) {
    //     error += QObject::tr("Failed to set motion status. ") + "\n";
    // }

    // if (!error.isEmpty()) {
    //     emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    // }
    // FREQ_LOG_PRINT_TIMESTAMP_THREAD
}

void RobotParameters::getSevenLoadMotionStatus(AbstractCmd *absCmd)
{
    // FREQ_LOG_PRINT_TIMESTAMP_THREAD
    // int status;
    // int ret = _IRobotArm->getSevenLoadMotionStatus(status);
    // QString error;
    // if (ret != ERROR_OK) {
    //     error += QObject::tr("Failed to get motion status. ") + "\n";
    // }

    // if (!error.isEmpty()) {
    //     emit CommunicationEngine::instance()->signal_needMainWidgetWarning(error);
    // }

    // if(ret == ERROR_OK) {
    //     emit CommunicationEngine::instance()->signal_setSevenMotion_status(status);
    // }

            // FREQ_LOG_PRINT_TIMESTAMP_THREAD
}

void RobotParameters::getParamRangeDoubleValue(
    InoRobBusiness::IRobotParamRange *param,
    const std::string &structName, const std::string &name,
    QList<double> &minList, QList<double> &maxList)
{
    minList.push_back(param->getDoubleMinValue(structName, name));
    maxList.push_back(param->getDoubleMaxValue(structName, name));
}

void RobotParameters::getParamRangeDoubleValue(
    InoRobBusiness::IRobotParamRange *param,
    const std::string &structName, const std::vector<std::string> &paraNameVec,
    QList<double> &minList, QList<double> &maxList)
{
    for (const std::string &name : paraNameVec) {
        getParamRangeDoubleValue(param, structName, name, minList, maxList);
    }
}
