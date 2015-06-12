#include "Outlet.h"

#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#define RELAY_PIN_1 4
#define RELAY_PIN_2 5
#define RELAY_PIN_3 6
#define RELAY_PIN_4 7

class RelayManager {
  public:
    RelayManager();
    void updateRelaySignal(Outlet* outlets[]);
  private:
    int relayPins[4];
    int* relaySignals;
};

#endif
