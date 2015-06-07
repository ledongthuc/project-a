#include "OutletStatus.h"

#ifndef OUTLET_H_
#define OUTLET_H_


class Outlet {
  public:
    OutletStatus status;
  private:
    Outlet();
    Outlet(bool isExist, bool status);
    Outlet(OutletStatus outletStatus);
    void updateStatus(OutletStatus outletStatus);
    OutletStatus getStatus();
};

#endif
