#ifndef _MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
#define _MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_

#include "modify_strategy.h"
#include "probability_strategy.h"
#include <memory>

namespace genericdp {

template <typename T>
class ModifyStrategyStochasticDecorator : public ModifyStrategy<T> {
  ModifyStrategyStochasticDecorator(
      std::shared_ptr<ModifyStrategy<T>> strat,
      std::shared_ptr<ProbabilityStrategy<T>> prob)
      : strat_(strat), prob_(prob) {}
  virtual void Modify(T *state) const {
    strat_->Modify(state);
    state->probability *= prob_->GetProbablity(state);
  }
  std::shared_ptr<ModifyStrategy<T>> strat_;
  std::shared_ptr<ProbabilityStrategy<T>> prob_;
};

} // namespace genericdp

#endif //_MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
