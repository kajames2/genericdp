#ifndef _SINGLE_VECTOR_DP_STORAGE_H_
#define _SINGLE_VECTOR_DP_STORAGE_H_

#include "dp_storage.h"
#include <memory>
#include <vector>

namespace genericdp {
template <typename Key, typename Result>
class SingleVectorDPStorage : public DPStorage<Key, Result> {
public:
  const Result &GetOptimalResult(const Key &state) const;
  virtual bool IsTerminalState(const Key &state) const = 0;
  bool IsStoredState(const Key &state) const;
  double GetOptimalValue(const Key &state) const;
  void StoreOptimalResult(const Key &state, Result opt_result, double value);

  SingleVectorDPStorage() = default;
  SingleVectorDPStorage(const SingleVectorDPStorage &) = delete;
  SingleVectorDPStorage &operator=(const SingleVectorDPStorage &) = delete;
  virtual ~SingleVectorDPStorage() {}

protected:
  virtual bool IsValidState(const Key &state) const = 0;
  virtual int GetIndex(const Key &state) const = 0;

  std::vector<Result> result_table_;
  std::vector<double> value_table_;
  std::vector<bool> is_stored_table_;
};

template <typename Key, typename Result>
bool SingleVectorDPStorage<Key, Result>::IsStoredState(const Key &state) const {
  return is_stored_table_.at(GetIndex(state));
}

template <typename Key, typename Result>
double
SingleVectorDPStorage<Key, Result>::GetOptimalValue(const Key &state) const {
  return value_table_.at(GetIndex(state));
}

template <typename Key, typename Result>
const Result &
SingleVectorDPStorage<Key, Result>::GetOptimalResult(const Key &state) const {
  return result_table_.at(GetIndex(state));
}

template <typename Key, typename Result>
void SingleVectorDPStorage<Key, Result>::StoreOptimalResult(const Key &state,
                                                            Result opt_result,
                                                            double value) {
  result_table_.at(GetIndex(state)) = opt_result;
  value_table_.at(GetIndex(state)) = value;
  is_stored_table_.at(GetIndex(state)) = true;
}

} // namespace genericdp
#endif // _SINGLE_VECTOR_DP_STORAGE_H_
