#ifndef _GENERICDP_RESULT_SET_H_
#define _GENERICDP_RESULT_SET_H_

#include <ostream>
#include <vector>

#include "genericdp/result.h"

namespace genericdp {

template <typename State, typename Policy>
class ResultSet {
 public:
  ResultSet() = default;
  ResultSet(Result<State, Policy> res);

  void AddResultSet(ResultSet& other);
  void AddResult(Result<State, Policy>& result);
  Result<State, Policy>& operator[](int i) { return results_[i]; }
  const Result<State, Policy>& operator[](int i) const { return results_[i]; }

  float GetValue() const { return value_; }
  int size() const { return results_.size(); }

 private:
  std::vector<Result<State, Policy>> results_ = {};
  float value_ = 0;
};

template <typename State, typename Policy>
ResultSet<State, Policy>::ResultSet(Result<State, Policy> res) {
  AddResult(res);
}

template <typename State, typename Policy>
void ResultSet<State, Policy>::AddResult(Result<State, Policy>& res) {
  value_ += res.valuation.value * res.valuation.probability;
  results_.push_back(std::move(res));
}

template <typename State, typename Policy>
void ResultSet<State, Policy>::AddResultSet(ResultSet& other) {
  for (auto& result : other.results_) {
    AddResult(result);
  }
}

template <typename State, typename Policy>
std::ostream& operator<<(std::ostream& out,
                         const ResultSet<State, Policy> res) {
  for (int i = 0; i < res.size()-1; ++i) {
    out << res[i] << '\n';
  }
  out << res[res.size()-1];
  return out;
}

}  // namespace genericdp
#endif  // _GENERICDP_RESULT_DP_H_
