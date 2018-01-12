#ifndef _MODIFY_STRATEGY_COMPOSITE_H_
#define _MODIFY_STRATEGY_COMPOSITE_H_

#include "modify_strategy.h"
#include <memory>
#include <vector>

namespace genericdp {

template <typename T> class ModifyStrategyComposite : public ModifyStrategy<T> {
  ModifyStrategyComposite() : strats_() {}

  void AddStrategy(std::shared_ptr<ModifyStrategy<T>> strat) {
    strats_.push_back(strat);
  }

  virtual void Modify(T *state) override {
    for (auto strat : strats_) {
      strat->ModifyStrategy(state);
    }
  }

private:
  std::vector<std::shared_ptr<const ModifyStrategy<T>>> strats_;
};

} // namespace genericdp

#endif //_MODIFY_STRATEGY_COMPOSITE_H_
