#include "OutletStatus.h"

#ifndef OUTLET_SIGNAL_PARSER_H
#define OUTLET_SIGNAL_PARSER_H

class OutletSignalParser {
  public:
    void parseOutletSignal(unsigned char signal, OutletStatus outletStatus[]);
    unsigned char parseCurrentSignalByUpdatedSignal(unsigned char currentSignal, unsigned char updatedSignal);
};

#endif
