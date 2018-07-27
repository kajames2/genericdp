#ifndef _GENERICDP_PROBABILITY_INVERSE_H_
#define _GENERICDP_PROBABILITY_INVERSE_H_

#include <memory>
#include <utility>

#include "genericdp/probability.h"

namespace genericdp {
namespace probability {

template <typename T>
class Inverse : public Probability<T> {
 public:
  explicit Inverse(std::unique_ptr<const Probability<T>> prob)
      : prob_(std::move(prob)) {}
  double GetProbability(const T &state) const {
    return 1 - prob_->GetProbability(state);
  }

 private:
  std::unique_ptr<const Probability<T>> prob_;
};

}  // namespace probability
}  // namespace genericdp
#endif  // _GENERICDP_PROBABILITY_INVERSE_H_
