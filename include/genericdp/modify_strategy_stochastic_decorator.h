#ifndef _MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
#define _MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_

#include "modify_strategy.h"
#include "probability_strategy.h"
#include <memory>

namespace genericdp {

template <typename T>
class ModifyStrategyStochasticDecorator : public ModifyStrategy<T> {
public:
  ModifyStrategyStochasticDecorator(
      std::shared_ptr<const ModifyStrategy<T>> strat,
      std::shared_ptr<const ProbabilityStrategy<T>> prob)
      : strat_(strat), prob_(prob) {}
  virtual void Modify(T *state) const {
    strat_->Modify(state);
    state->probability *= prob_->GetProbability(*state);
  }

private:
  std::shared_ptr<const ModifyStrategy<T>> strat_;
  std::shared_ptr<const ProbabilityStrategy<T>> prob_;
};

} // namespace genericdp

#endif //_MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
