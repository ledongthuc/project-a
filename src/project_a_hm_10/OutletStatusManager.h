#include "OutletSignalParser.h"
#include "Outlet.h"

#ifndef OUTLET_MANAGER_H
#define OUTLET_MANAGER_H

class OutletStatusManager {
  public:
    OutletStatusManager(int numberOfOutlet);
    void parseRequestFromMobile(unsigned char signal);
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
