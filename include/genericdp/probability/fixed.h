#ifndef _GENERICDP_PROBABILITY_FIXED_H_
#define _GENERICDP_PROBABILITY_FIXED_H_

#include "genericdp/probability.h"

namespace genericdp {
namespace probability {

template <typename T>
class Fixed : public Probability<T> {
 public:
  explicit Fixed(double prob) : prob_(prob) {}
  double GetProbability(const T &state) const override { return prob_; }

 private:
  double prob_;
};

}  // namespace probability
}  // namespace genericdp
#endif  // _GENERICDP_PROBABILITY_FIXED_H_
