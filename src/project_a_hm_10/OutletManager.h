#include "OutletSignalParser.h"
#include "Outlet.h"

#ifndef OUTLET_MANAGER_H
#define OUTLET_MANAGER_H

class OutletManager {
  public:
    OutletManager(int numberOfOutlet);
    void UpdateOutletStatus(char signal);
    char GetOutletSignal();
  private:
    int numberOfOutlet;
    Outlet outlets[];
    OutletSignalParser signalParser;
};

#endif
