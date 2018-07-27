#ifndef _GENERICDP_PROBABILITY_H_
#define _GENERICDP_PROBABILITY_H_

namespace genericdp {

template <typename T>
class Probability {
 public:
  virtual double GetProbability(const T &state) const = 0;
  virtual ~Probability() {}
};

}  // namespace genericdp

#endif  // _GENERICDP_PROBABILITY_H_
