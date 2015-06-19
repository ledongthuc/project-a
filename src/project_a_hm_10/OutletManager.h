#include "OutletSignalParser.h"
#include "Outlet.h"

#ifndef OUTLET_MANAGER_H
#define OUTLET_MANAGER_H

class OutletManager {
  public:
    OutletManager(int numberOfOutlet);
    void updateOutletStatus(unsigned char signal);
    void setOutletSignal(unsigned char signal);
    unsigned char getOutletSignal();
    Outlet** getOutlets();
  private:
    int numberOfOutlet;
    Outlet* outlets[4];
    unsigned char signal;
    OutletSignalParser* signalParser;
};

#endif
