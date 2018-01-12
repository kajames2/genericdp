#ifndef _PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_
#define _PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_

#include "probability_strategy.h"
#include <memory>

namespace genericdp {

template <typename T>
class ProbabilityStrategyInverseDecorator : public ProbabilityStrategy<T>{
 public:
  double GetProbability(const T &state) const {
    return 1 - prob_->GetProbability(state);
  };

  std::shared_ptr<ProbabilityStrategy<T>> prob_;
};

}  // namespace genericdp

#endif  //_PROBABILITY_STRATEGY_INVERSE_DECORATOR_H_
