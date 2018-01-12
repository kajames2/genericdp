#ifndef _PROBABILITY_STRATEGY_H_
#define _PROBABILITY_STRATEGY_H_

namespace genericdp {

template <typename T>
class ProbabilityStrategy {
 public:
  virtual double GetProbability(const T &state) const = 0;
};

}  // namespace genericdp

#endif  //_PROBABILITY_STRATEGY_H_
