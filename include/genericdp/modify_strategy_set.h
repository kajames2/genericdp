#ifndef _GENERICDP_MODIFY_STRATEGY_SET_H_
#define _GENERICDP_MODIFY_STRATEGY_SET_H_

#include <memory>
#include <vector>

#include "genericdp/modify_strategy.h"
#include "genericdp/modify_strategy_stochastic_decorator.h"
#include "genericdp/probability_strategy_inverse_decorator.h"

namespace genericdp {

template <typename T>
class ModifyStrategySet {
 public:
  using const_iterator = typename std::vector<
      std::shared_ptr<const ModifyStrategy<T>>>::const_iterator;
  ModifyStrategySet() : strats_() {}
  ModifyStrategySet(std::shared_ptr<const ModifyStrategy<T>> if_choice,
                    std::shared_ptr<const ModifyStrategy<T>> else_choice,
                    std::shared_ptr<const ProbabilityStrategy<T>> prob)
      : strats_() {
    auto if_strat =
        std::make_shared<const ModifyStrategyStochasticDecorator<T>>(if_choice,
                                                                     prob);
    auto else_prob =
        std::make_shared<const ProbabilityStrategyInverseDecorator<T>>(prob);
    auto else_strat =
        std::make_shared<const ModifyStrategyStochasticDecorator<T>>(
            else_choice, else_prob);
    AddStrategy(if_strat);
    AddStrategy(else_strat);
  }
  void AddStrategy(std::shared_ptr<const ModifyStrategy<T>> strat) {
    strats_.push_back(strat);
  }

  const_iterator begin() const noexcept { return strats_.begin(); };

  const_iterator end() const noexcept { return strats_.end(); };

 private:
  std::vector<std::shared_ptr<const ModifyStrategy<T>>> strats_;
};

}  // namespace genericdp
#endif  // _GENERICDP_MODIFY_STRATEGY_SET_H_
