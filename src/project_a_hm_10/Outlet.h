#include "OutletStatus.h"

#ifndef OUTLET_H_
#define OUTLET_H_


class Outlet {
  public:
    Outlet();
    Outlet(bool isExist, bool status);
    Outlet(OutletStatus outletStatus);
    void setStatus(OutletStatus outletStatus);
    OutletStatus getStatus();
  private:
    OutletStatus status;
};

#endif