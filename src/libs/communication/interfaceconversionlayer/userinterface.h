#pragma once

#include "communication_global.h"
#include "ctrlauthority.h"
#include "projectdata.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT UserInterface
{
public:
    UserInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    InoUserMode getCurrentLoginUserMode();
    bool userLogin(const InoUserMode &mode, const QString &passwd);

    bool setCtlAuthority(const InoCtrlAuthority &authority);
    InoCtrlAuthority getCtlAuthority();
};
