#ifndef _STOCHASTIC_DP_RESULT_H_
#define _STOCHASTIC_DP_RESULT_H_

#include "dp_result.h"
#include "endogenous_state.h"
#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class StochasticDPResult : public DPResult<T> {
public:
  StochasticDPResult(std::unique_ptr<const ExogenousState<T>> ex,
                     std::unique_ptr<const EndogenousState<T>> end, double val,
                     double probability);
  StochasticDPResult() : DPResult<T>(), probability_(0) {}

  StochasticDPResult(const StochasticDPResult &other);
  StochasticDPResult &operator=(const StochasticDPResult &other);
  StochasticDPResult(StochasticDPResult &&) = default;
  StochasticDPResult &operator=(StochasticDPResult &&) = default;

  std::string GetString() const override;
  std::string GetHeader() const override;
  double GetProbability() const { return probability_; }

private:
  double probability_;
};

template <class T>
StochasticDPResult<T>::StochasticDPResult(
    std::unique_ptr<const ExogenousState<T>> ex,
    std::unique_ptr<const EndogenousState<T>> end, double val,
    double probability)
    : DPResult<T>(std::move(ex), std::move(end), val), probability_(probability) {}

template <class T>
StochasticDPResult<T>::StochasticDPResult(const StochasticDPResult &other)
    : DPResult<T>(other),
      probability_(other.probability_) {}

template <class T>
StochasticDPResult<T> &StochasticDPResult<T>::
operator=(const StochasticDPResult &other) {
  using std::swap;
  StochasticDPResult copy(other);
  swap(*this, copy);
  return *this;
}

template <class T> std::string StochasticDPResult<T>::GetString() const {
  return std::to_string(probability_) + ", " + DPResult<T>::GetString();
}

template <class T> std::string StochasticDPResult<T>::GetHeader() const {
  return std::string("Probability") + ", " + DPResult<T>::GetHeader();
}
}
#endif // _STOCHASTIC_DP_RESULT_H_
