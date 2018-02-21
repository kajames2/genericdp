#ifndef _GENERICDP_DP_STATE_H_
#define _GENERICDP_DP_STATE_H_

#include <memory>

namespace genericdp {
template <typename T>
class DPState {
 public:
  DPState()
      : probability(1),
        immediate_value(0),
        future_value(0),
        value(0),
        domain() {}
  explicit DPState(T in_domain)
      : probability(1),
        immediate_value(0),
        future_value(0),
        value(0),
        domain(in_domain) {}

  T domain;
  double probability;
  double immediate_value;
  double future_value;
  double value;
};

}  // namespace genericdp

#endif  // _GENERICDP_DP_STATE_H_
