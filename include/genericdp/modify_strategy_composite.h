#ifndef _MODIFY_STRATEGY_COMPOSITE_H_
#define _MODIFY_STRATEGY_COMPOSITE_H_

#include "modify_strategy.h"
#include "dp_state.h"
#include <memory>
#include <vector>

namespace genericdp {

template <typename T> class ModifyStrategyComposite : public ModifyStrategy<T> {
 public:
  ModifyStrategyComposite() : strats_() {}

  void AddStrategy(std::shared_ptr<const ModifyStrategy<T>> strat) {
    strats_.push_back(strat);
  }

  virtual void Modify(DPState<T> *state) const override {
    for (std::shared_ptr<const ModifyStrategy<T>> strat : strats_) {
      strat->Modify(state);
    }
  }

private:
  std::vector<std::shared_ptr<const ModifyStrategy<T>>> strats_;
};

} // namespace genericdp

#endif //_MODIFY_STRATEGY_COMPOSITE_H_
