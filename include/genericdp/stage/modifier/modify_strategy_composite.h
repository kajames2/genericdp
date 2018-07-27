#ifndef _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_
#define _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_

#include <memory>
#include <utility>
#include <vector>

#include "genericdp/modify_strategy.h"
#include "genericdp/modify_strategy_set.h"
#include "genericdp/state.h"

namespace genericdp {

template <typename InState, typename OutDec>
class ModifyStrategyComposite : public ModifyStrategy<InState, OutDec>,
                                private ModifyStrategySet<InState, OutDec> {
 public:
  ModifyStrategyComposite() : strats_() {}

  void Modify(State<InState, OutDec>* state) const override {
    for (auto it = begin(); it != end(); ++it) {
      (*it)->Modify(state);
    }
  }
};

}  // namespace genericdp

#endif  // _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_
