#include "OutletSignalParser.h"
#include "Outlet.h"

#ifndef OUTLET_MANAGER_H
#define OUTLET_MANAGER_H

class OutletManager {
  public:
    OutletManager(int numberOfOutlet);
    void updateOutletStatus(char signal);
    void setOutletSignal(char signal);
    char getOutletSignal();
  private:
    int numberOfOutlet;
    Outlet* outlets[4];
    char signal;
    OutletSignalParser* signalParser;
};

#endif
