#include "labelinterface.h"
#include "communication.h"
#include "IController.h"
#include "metatypeconversion.h"
#include "cobotlogex.h"
#include "common/common.h"
#include "modulesutils.h"
#include "stringutils.h"

bool LabelInterface::readAllLabels()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetLabel()->ReadLabels();
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::saveAllLabels()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->SaveLabels();
    if (ret != ERR_OK) {
        return false;
    }

    comm()->project()->updateLablesToTransfor();

    comm()->project()->sendSyncFlag(
        static_cast<int>(InoRobBusiness::SyncProjcetInfoType::SYNC_LABEL_INFO));
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

QVector<InoLabelItem> LabelInterface::genInitIoItems(
    const InoLabelType &labelType, const InoLabelIOType &ioType,
    const ShowType &dataType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    std::vector<LabelItem> vItems = comm()->project()->GetLabel()->GenInitIoItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType),
        MetaTypeConversion::inoApi2tp_ioType(ioType),
        MetaTypeConversion::inoApi2tp_dataType(dataType));

    if (vItems.empty()) {
        return QVector<InoLabelItem>();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_Items(vItems);
}

QVector<InoLabelItem> LabelInterface::genInitAaDaItems(
    const InoLabelType &labelType, const InoAdDaType &addaType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    std::vector<LabelItem> vItems = comm()->project()->GetLabel()->GenInitAdDaItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType),
        MetaTypeConversion::inoApi2tp_addaType(addaType));

    if (vItems.empty()) {
        return QVector<InoLabelItem>();
    }

    FREQ_LOG_PRINT_TIMESTAMP
        return MetaTypeConversion::tp2InoApi_Items(vItems);
}

QVector<InoLabelItem> LabelInterface::genInitOtherItems(
    const InoLabelType &labelType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    std::vector<LabelItem> vItems = comm()->project()->GetLabel()->GenInitOtherItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType));
    if (vItems.empty()) {
        return QVector<InoLabelItem>();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_Items(vItems);
}

QVector<InoLabelItem> LabelInterface::getIoItems(const InoLabelType &labelType,
                                                 const InoLabelIOType &ioType,
                                                 const ShowType &dataType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    IoLabelItems items = comm()->project()->GetLabel()->GetIoItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType),
        MetaTypeConversion::inoApi2tp_ioType(ioType),
        MetaTypeConversion::inoApi2tp_dataType(dataType));
    if (items.nNumberOfLabels <= 0) {
        return QVector<InoLabelItem>();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_Items(items.LabelsArray);
}

QVector<InoLabelItem> LabelInterface::getAdDaItems(
    const InoLabelType &labelType, const InoAdDaType &addaType )
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    IoLabelItems items = comm()->project()->GetLabel()->getAdDaItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType),
        MetaTypeConversion::inoApi2tp_addaType(addaType));
    if (items.nNumberOfLabels <= 0) {
        return QVector<InoLabelItem>();
    }

    FREQ_LOG_PRINT_TIMESTAMP
        return MetaTypeConversion::tp2InoApi_Items(items.LabelsArray);
}

QVector<InoLabelItem> LabelInterface::getOtherItems(
    const InoLabelType &labelType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QVector<InoLabelItem>();
    }

    IoLabelItems items = comm()->project()->GetLabel()->GetItems(
        MetaTypeConversion::inoApi2tp_labelType(labelType));
    if (items.nNumberOfLabels <= 0) {
        return QVector<InoLabelItem>();
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_Items(items.LabelsArray);
}

int LabelInterface::getIoStartIndex(const InoLabelIOType &ioType,
                                    const ShowType &dataType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return -1;
    }

    return comm()->project()->GetLabel()->GetIoStartIndex(
        MetaTypeConversion::inoApi2tp_ioType(ioType),
        MetaTypeConversion::inoApi2tp_dataType(dataType));
}

int LabelInterface::getIoEndIndex(const InoLabelIOType &ioType,
                                  const ShowType &dataType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return -1;
    }

    return comm()->project()->GetLabel()->GetIoEndIndex(
        MetaTypeConversion::inoApi2tp_ioType(ioType),
        MetaTypeConversion::inoApi2tp_dataType(dataType));
}

int LabelInterface::getAdDaStartIndex(const InoAdDaType &addaType)
{
    if (addaType == InoAdDaType_IRLink) {
        return IRLINK_LABEL_START;
    } else if (addaType == InoAdDaType_EtherCAT) {
        return ETHERCAT_LABEL_START;
    }

    return INVALID_INDEX;
}

int LabelInterface::getAdDaEndIndex(const InoAdDaType &addaType)
{
    if (addaType == InoAdDaType_IRLink) {
        return IRLINK_LABEL_END;
    } else if (addaType == InoAdDaType_EtherCAT) {
        return ETHERCAT_LABEL_END;
    }

    return INVALID_INDEX;
}

QString LabelInterface::getItemLabel(const InoLabelType &labelType, int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return QString();
    }

    LabelItem labelItem = comm()->project()->GetLabel()->GetLabelItem(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex);
    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(labelItem.sLabel);
}

QString LabelInterface::getItemDescription(const InoLabelType &labelType, int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!isStatusOK()) {
        return QString();
    }

    LabelItem labelItem = comm()->project()->GetLabel()->GetLabelItem(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex);
    FREQ_LOG_PRINT_TIMESTAMP
        return QString::fromStdString(labelItem.sDescription);
}

bool LabelInterface::modifyIoItemLabel(const InoLabelType &labelType,
                                       const InoLabelIOType &ioType,
                                       const ShowType &dataType,
                                       int nIndex,
                                       const QString &sLabel)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int nEndIndex = getIoEndIndex(ioType, dataType);
    if (nIndex > nEndIndex) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemLabel(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sLabel.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::modifyAdDaItemLabel(const InoLabelType &labelType,
                                       const InoAdDaType &addaType,
                                       int nIndex, const QString &sLabel)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!isStatusOK()) {
        return false;
    }

    int nEndIndex = getAdDaEndIndex(addaType);
    if (nIndex > nEndIndex) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemLabel(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sLabel.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
        return (ret == ERR_OK);
}

bool LabelInterface::modifyOtherItemLabel(const InoLabelType &labelType,
                                          int nIndex, const QString &sLabel)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemLabel(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sLabel.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::modifyIoItemDescription(const InoLabelType &labelType,
                                             const InoLabelIOType &ioType,
                                             const ShowType &dataType,
                                             int nIndex,
                                             const QString &sDescription)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    if (InoLabelIOType_ToolIO == ioType) { // 工具IO默认描述暂不支持修改
        return true;
    }

    int nEndIndex = getIoEndIndex(ioType, dataType);
    if (nIndex > nEndIndex) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemDescription(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sDescription.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::updateIoItemDescription(const InoLabelType &labelType,
                                             int nIndex, const QString &sDescription)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemDescription(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sDescription.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::modifyAdDaItemDescription(const InoLabelType &labelType,
                                               const InoAdDaType &addaType,
                                               int nIndex,
                                               const QString &sDescription)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int nEndIndex = getAdDaEndIndex(addaType);
    if (nIndex > nEndIndex) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemDescription(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sDescription.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::modifyOtherItemDescription(
    const InoLabelType &labelType, int nIndex, const QString &sDescription)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    int ret = comm()->project()->GetLabel()->ModifyItemDescription(
        MetaTypeConversion::inoApi2tp_labelType(labelType), nIndex,
        sDescription.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool LabelInterface::modifyIoItem(
    const InoLabelType &labelType, const InoLabelIOType &ioType,
    const ShowType &dataType, const InoLabelItem &item)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    bool ret = modifyIoItemLabel(labelType, ioType, dataType, item.nIndex,
                                 item.sLabel);
    if (!ret) {
        return false;
    }

    ret = modifyIoItemDescription(labelType, ioType, dataType, item.nIndex,
                                  item.sDescription);
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool LabelInterface::modifyAdDaItem(
    const InoLabelType &labelType, const InoAdDaType &addaType,
    const InoLabelItem &item)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

        if (!isStatusOK()) {
        return false;
    }

    bool ret = modifyAdDaItemLabel(labelType, addaType, item.nIndex,
                                   item.sLabel);
    if (!ret) {
        return false;
    }

    ret = modifyAdDaItemDescription(labelType, addaType, item.nIndex,
                                    item.sDescription);
    FREQ_LOG_PRINT_TIMESTAMP
        return ret;
}

bool LabelInterface::modifyOtherItem(const InoLabelType &labelType,
                                     const InoLabelItem &item)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!isStatusOK()) {
        return false;
    }

    bool ret = modifyOtherItemLabel(labelType, item.nIndex, item.sLabel);
    if (!ret) {
        return false;
    }

    ret = modifyOtherItemDescription(labelType, item.nIndex, item.sDescription);
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

InoLabelType LabelInterface::getLabelType(const QString &namePrefix)
{
    InoLabelType labelType = IO_INPUT_BIT;
    if (0 == namePrefix.compare("In", Qt::CaseInsensitive)) {
        labelType = IO_INPUT_BIT;
    } else if (0 == namePrefix.compare("InB", Qt::CaseInsensitive)) {
        labelType = IO_INPUT_BYTE;
    } else if (0 == namePrefix.compare("InW", Qt::CaseInsensitive)) {
        labelType = IO_INPUT_WORD;
    } else if (0 == namePrefix.compare("Out", Qt::CaseInsensitive)) {
        labelType = IO_OUTPUT_BIT;
    } else if (0 == namePrefix.compare("OutB", Qt::CaseInsensitive)) {
        labelType = IO_OUTPUT_BYTE;
    } else if (0 == namePrefix.compare("OutW", Qt::CaseInsensitive)) {
        labelType = IO_OUTPUT_WORD;
    }

    return labelType;
}

bool LabelInterface::isToolIoItemDescLangCorrect()
{
    QString lang = Common::instance()->getConfigInfo().m_language;
    if (lang.isEmpty()) {
        lang = "en_US";
    }

    bool isContainsEmptyLabel = false;
    QList<bool> chineseDescList;
    for (int lType = IO_INPUT_BIT; lType <= IO_OUTPUT_WORD; lType++) {
        InoLabelType labelType = static_cast<InoLabelType>(lType);
        for (int sType = ShowType_Bit; sType < ShowType_Size; sType++) {
            ShowType showType = static_cast<ShowType>(sType);
            int nStartIndex = this->getIoStartIndex(InoLabelIOType_ToolIO, showType);
            int nEndIndex = this->getIoEndIndex(InoLabelIOType_ToolIO, showType);

            for (int nIndex = nStartIndex; nIndex <= nEndIndex; nIndex++) {
                QString sDesc = this->getItemDescription(labelType, nIndex);
                if (sDesc.isEmpty()) {
                    isContainsEmptyLabel = true;
                    continue;
                }

                chineseDescList << StringUtils::isContainChinese(sDesc);
            }
        }
    }

    if ((lang.compare("zh_CN") && chineseDescList.contains(true))
        || (!lang.compare("zh_CN") && !chineseDescList.contains(true))
        || !isContainsEmptyLabel) {
        return false;
    }

    return true;
}

bool LabelInterface::isStatusOK()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (comm()->project()
        && comm()->project()->GetLabel()) {
        return true;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return false;
}
