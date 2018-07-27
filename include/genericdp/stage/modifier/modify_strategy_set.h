#ifndef _GENERICDP_MODIFY_STRATEGY_SET_H_
#define _GENERICDP_MODIFY_STRATEGY_SET_H_

#include <memory>
#include <utility>
#include <vector>

#include "genericdp/modify_strategy.h"
#include "genericdp/modify_strategy_stochastic_decorator.h"
#include "genericdp/probability_strategy_inverse_decorator.h"

namespace genericdp {

template <typename InState, typename OutDec>
class ModifyStrategySet {
 public:
  // Just a vector of unique_ptrs to const ModifyStrategies.
  using ModifyVec =
      std::vector<std::unique_ptr<const ModifyStrategy<InState, OutDec>>>;
  ModifyStrategySet() : strats_() {}

  void AddStrategy(
      std::unique_ptr<const ModifyStrategy<InState, OutDec>> strat) {
    strats_.push_back(std::move(strat));
  }

  typename ModifyVec::const_iterator begin() const noexcept {
    return strats_.begin();
  };
  typename ModifyVec::const_iterator end() const noexcept {
    return strats_.end();
  };

 private:
  ModifyVec strats_;
};

template <typename T>
ModifyStrategySet<T> BinaryChoiceSet(
    std::unique_ptr<const ModifyStrategy<T>> if_choice,
    std::unique_ptr<const ModifyStrategy<T>> else_choice,
    std::shared_ptr<const ProbabilityStrategy<T>> prob) {
  auto if_strat = std::make_unique<const ModifyStrategyStochasticDecorator<T>>(
      std::move(if_choice), prob);
  auto else_prob =
      std::make_shared<const ProbabilityStrategyInverseDecorator<T>>(prob);
  auto else_strat =
      std::make_unique<const ModifyStrategyStochasticDecorator<T>>(
          std::move(else_choice), else_prob);
  ModifyStrategySet<T> set;
  set.AddStrategy(std::move(if_strat));
  set.AddStrategy(std::move(else_strat));
  return set;
}

}  // namespace genericdp
#endif  // _GENERICDP_MODIFY_STRATEGY_SET_H_
