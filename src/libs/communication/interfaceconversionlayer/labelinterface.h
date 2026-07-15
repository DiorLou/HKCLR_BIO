#pragma once

#include "communication_global.h"
#include "labeldata.h"
#include <QVector>

namespace InoRobBusiness
{
class IController;
class IProject;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT LabelInterface
{
public:
    LabelInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // read all labels from files to cache
    bool readAllLabels();
    // save all labels
    bool saveAllLabels();

    // init items
    // IN/OUT
    QVector<InoLabelItem> genInitIoItems(const InoLabelType &labelType,
                                         const InoLabelIOType &ioType,
                                         const ShowType &dataType);
    // AD/DA
    QVector<InoLabelItem> genInitAaDaItems(const InoLabelType &labelType,
                                           const InoAdDaType &addaType);

    //B/R/D
    QVector<InoLabelItem> genInitOtherItems(const InoLabelType &labelType);

    // get items
    // IN/OUT
    QVector<InoLabelItem> getIoItems(const InoLabelType &labelType,
                                     const InoLabelIOType &ioType,
                                     const ShowType &dataType);
    // AD/DA
    QVector<InoLabelItem> getAdDaItems(const InoLabelType &labelType,
                                       const InoAdDaType &addaType);

    // B/R/D
    QVector<InoLabelItem> getOtherItems(const InoLabelType &labelType);

    // index
    int getIoStartIndex(const InoLabelIOType &ioType,
                        const ShowType &dataType);

    int getIoEndIndex(const InoLabelIOType &ioType,
                      const ShowType &dataType);

    // AD/DA
    int getAdDaStartIndex(const InoAdDaType &addaType);
    int getAdDaEndIndex(const InoAdDaType &addaType);

    QString getItemLabel(const InoLabelType &labelType, int nIndex);
    QString getItemDescription(const InoLabelType &labelType, int nIndex);

    // modify sLabel
    // IN/OUT
    bool modifyIoItemLabel(const InoLabelType &labelType,
                           const InoLabelIOType &ioType,
                           const ShowType &dataType,
                           int nIndex, const QString &sLabel);
    // AD/DA
    bool modifyAdDaItemLabel(const InoLabelType &labelType,
                             const InoAdDaType &addaType,
                             int nIndex, const QString &sLabel);

    // B/R/D
    bool modifyOtherItemLabel(const InoLabelType &labelType,
                              int nIndex, const QString &sLabel);

    // modify description
    // IN/OUT
    bool modifyIoItemDescription(const InoLabelType &labelType,
                                 const InoLabelIOType &ioType,
                                 const ShowType &dataType,
                                 int nIndex, const QString &sDescription);
    // IN/OUT
    bool updateIoItemDescription(const InoLabelType &labelType,
                                 int nIndex, const QString &sDescription);
    // AD/DA
    bool modifyAdDaItemDescription(const InoLabelType &labelType,
                                   const InoAdDaType &addaType,
                                   int nIndex, const QString &sDescription);

    // B/R/D
    bool modifyOtherItemDescription(const InoLabelType &labelType,
                                    int nIndex, const QString &sDescription);

    // IN/OUT
    bool modifyIoItem(const InoLabelType &labelType,
                      const InoLabelIOType &ioType,
                      const ShowType &dataType,
                      const InoLabelItem &item);

    // AD/DA
    bool modifyAdDaItem(const InoLabelType &labelType,
                        const InoAdDaType &addaType,
                        const InoLabelItem &item);

    // B/R/D
    bool modifyOtherItem(const InoLabelType &labelType,
                         const InoLabelItem &item);

    InoLabelType getLabelType(const QString &namePrefix);

    bool isToolIoItemDescLangCorrect();

private:
    bool isStatusOK();
};
