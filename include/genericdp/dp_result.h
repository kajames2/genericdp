#ifndef _DP_RESULT_H_
#define _DP_RESULT_H_

#include "dp_state.h"

#include <memory>
#include <vector>

namespace genericdp {
template <typename T> class DPResult {
public:
  DPResult();
  DPResult(const DPState<T> &state);

  void AddState(const DPState<T> &state) {
    probability_ += state.probability;
    immediate_value_ += state.immediate_value * state.probability;
    future_value_ += state.future_value * state.probability;
    value_ += state.value * state.probability;
    states_.push_back(state);
  }

  void AddResult(DPResult<T> other) {
    for (auto state : other.states_) {
      AddState(state);
    }
  }
  DPState<T> operator[](int i) { return states_[i]; }

  std::vector<DPState<T>> GetStates() { return states_; }
  double GetProbability() { return probability_; }
  double GetImmediateValue() { return immediate_value_; }
  double GetFutureValue() { return future_value_; }
  double GetValue() { return value_; }
  int GetSize() { return states_.size(); }

private:
  std::vector<DPState<T>> states_;
  double probability_;
  double immediate_value_;
  double future_value_;
  double value_;
};

template <typename T>
DPResult<T>::DPResult()
    : states_(), probability_(0), immediate_value_(0), future_value_(0),
      value_(0) {}

template <typename T>
DPResult<T>::DPResult(const DPState<T> &state)
    : states_(), probability_(0), immediate_value_(0), future_value_(0),
      value_(0) {
  AddState(state);
}
} // namespace genericdp
#endif // _DP_RESULT_H_
