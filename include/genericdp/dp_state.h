#ifndef _DP_STATE_H_
#define _DP_STATE_H_

#include <memory>

namespace genericdp {
class DPState {
public:
  DPState() : probability(1), immediate_value(0), future_value(0), value(0) {}
  void Reset() {
    probability = 1;
    immediate_value = 0;
    future_value = 1;
    value = 1;
  }
  
  double probability;
  double immediate_value;
  double future_value;
  double value;
};

} // namespace genericdp

#endif // _DP_STATE_H_
