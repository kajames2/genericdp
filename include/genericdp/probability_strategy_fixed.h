#ifndef _PROBABILITY_STRATEGY_FIXED_H_
#define _PROBABILITY_STRATEGY_FIXED_H_

#include "probability_strategy.h"

namespace genericdp {

template <typename T>
class ProbabilityStrategyFixed : public ProbabilityStrategy<T> {
 public:
  ProbabilityStrategyFixed(double prob) : prob_(prob) {}
  double GetProbability(const T &state) const override {return prob_;}

 private:
  double prob_;
};

}  // namespace genericdp

#endif  //_PROBABILITY_STRATEGY_FIXED_H_
