#ifndef _GENERICDP_PROBABILITY_STRATEGY_H_
#define _GENERICDP_PROBABILITY_STRATEGY_H_

namespace genericdp {

template <typename T>
class ProbabilityStrategy {
 public:
  virtual double GetProbability(const T &state) const = 0;
  virtual ~ProbabilityStrategy() {}
};

}  // namespace genericdp

#endif  // _GENERICDP_PROBABILITY_STRATEGY_H_
