#ifndef _PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_
#define _PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_

#include "probability_strategy.h"
#include <memory>

namespace genericdp {

template <typename T>
class ProbabilityStrategyInverseDecorator : public ProbabilityStrategy<T> {
public:
  ProbabilityStrategyInverseDecorator(
      std::shared_ptr<const ProbabilityStrategy<T>> prob)
      : prob_(prob) {}
  double GetProbability(const T &state) const {
    return 1 - prob_->GetProbability(state);
  };

private:
  std::shared_ptr<const ProbabilityStrategy<T>> prob_;
};

} // namespace genericdp

#endif //_PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_
