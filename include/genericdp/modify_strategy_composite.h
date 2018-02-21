#ifndef _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_
#define _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_

#include <memory>
#include <vector>

#include "genericdp/dp_state.h"
#include "genericdp/modify_strategy.h"

namespace genericdp {

template <typename T>
class ModifyStrategyComposite : public ModifyStrategy<T> {
 public:
  ModifyStrategyComposite() : strats_() {}

  void AddStrategy(std::shared_ptr<const ModifyStrategy<T>> strat) {
    strats_.push_back(strat);
  }

  void Modify(DPState<T> *state) const override {
    for (std::shared_ptr<const ModifyStrategy<T>> strat : strats_) {
      strat->Modify(state);
    }
  }

 private:
  std::vector<std::shared_ptr<const ModifyStrategy<T>>> strats_;
};

}  // namespace genericdp

#endif  // _GENERICDP_MODIFY_STRATEGY_COMPOSITE_H_
