#ifndef _GENERICDP_MODIFY_STRATEGY_H_
#define _GENERICDP_MODIFY_STRATEGY_H_

#include "genericdp/dp_state.h"

namespace genericdp {

template <typename T>
class ModifyStrategy {
 public:
  virtual void Modify(DPState<T> *state) const = 0;
  virtual ~ModifyStrategy() {}
};

}  // namespace genericdp

#endif  // _GENERICDP_MODIFY_STRATEGY_H_
