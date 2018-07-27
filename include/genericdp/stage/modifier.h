#ifndef _GENERICDP_STATE_MODIFICATION_H_
#define _GENERICDP_STATE_MODIFICATION_H_

#include "genericdp/state.h"

namespace genericdp {

template <typename InState, typename OutDec>
class StateModification {
 public:
  virtual void Modify(State<InState, OutDec>& state) const = 0;
  virtual ~StateModification() {}
};

}  // namespace genericdp

#endif  // _GENERICDP_STATE_MODIFICATION_H_
