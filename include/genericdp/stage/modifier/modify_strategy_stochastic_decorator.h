#ifndef _GENERICDP_MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
#define _GENERICDP_MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_

#include <memory>

#include "genericdp/modify_strategy.h"
#include "genericdp/probability_strategy.h"
#include "genericdp/state.h"

namespace genericdp {

template <typename InState, typename OutDec>
class ModifyStrategyStochasticDecorator
    : public ModifyStrategy<InState, OutDec> {
 public:
  ModifyStrategyStochasticDecorator(
      std::unique_ptr<const ModifyStrategy<InState, OutDec>> strat,
      std::shared_ptr<const ProbabilityStrategy<InState>> prob)
      : strat_(strat), prob_(prob) {}
  virtual void Modify(State<InState, OutDec> *state) const {
    strat_->Modify(state);
    state->probability *= prob_->GetProbability(*state);
  }

 private:
  std::unique_ptr<const ModifyStrategy<InState, OutDec>> strat_;
  std::shared_ptr<const ProbabilityStrategy<InState>> prob_;
};

}  // namespace genericdp

#endif  // _GENERICDP_MODIFY_STRATEGY_STOCHASTIC_DECORATOR_H_
