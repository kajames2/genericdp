#ifndef _SIMPLE_DP_STATE_H_
#define _SIMPLE_DP_STATE_H_

#include "dp_state.h"

namespace genericdptest {

class SimpleDPState : public genericdp::DPState {
public:
  SimpleDPState() : investment(0), period(0), cash(0), DPState() {}
  void Reset() {
    investment = 0;
    DPState::Reset();
  }
  int investment;
  int period;
  int cash;
};
}
#endif // _SIMPLE_DP_STATE_H_
