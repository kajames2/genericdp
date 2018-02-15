#ifndef _SIMPLE_STATE_H_
#define _SIMPLE_STATE_H_

#include "dp_state.h"

namespace genericdptest {

class SimpleState {
public:
  SimpleState() : investment(0), period(0), cash(0) {}
  int investment;
  int period;
  int cash;
};
}
#endif // _SIMPLE_STATE_H_
