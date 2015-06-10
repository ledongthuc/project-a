#include "OutletStatus.h"

#ifndef OUTLET_SIGNAL_PARSER_H
#define OUTLET_SIGNAL_PARSER_H

class OutletSignalParser {
  public:
    void parseOutletSignal(char signal, OutletStatus outletStatus[]);
};

#endif
