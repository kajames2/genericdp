#ifndef _FIXED_PROBABILITY_STRATEGY_H_
#define _FIXED_PROBABILITY_STRATEGY_H_

#include "probability_strategy.h"

namespace genericdp {

template <typename T>
class FixedProbabilityStrategy : public ProbabilityStrategy<T> {
 public:
  FixedProbabilityStrategy(double prob) : prob_(prob) {}
  double GetProbability(const T &state) const override {return prob_;}

 private:
  double prob_;
};

}  // namespace genericdp

#endif  //_FIXED_PROBABILITY_STRATEGY_H_
