#ifndef _GENERICDP_STORAGE_SINGLE_VECTOR_H_
#define _GENERICDP_STORAGE_SINGLE_VECTOR_H_

#include <cassert>
#include <memory>
#include <vector>

#include "genericdp/storage.h"

namespace genericdp {
namespace storage {

template <typename Key, typename Result>
class SingleVector : public Storage<Key, Result> {
 public:
  Result GetOptimalResult(const Key &state) const override;
  inline bool IsStoredState(const Key &state) const override;
  inline float GetOptimalValue(const Key &state) const override;
  inline void StoreOptimalResult(const Key &state, Result opt_result,
                                 float value) override;

  explicit SingleVector(int max_length);
  virtual ~SingleVector() {}

 private:
  virtual bool IsValidState(const Key &state) const = 0;
  virtual int GetIndex(const Key &state) const = 0;

  std::vector<Result> result_table_;
  std::vector<float> value_table_;
  std::vector<bool> is_stored_table_;
};

template <typename Key, typename Result>
SingleVector<Key, Result>::SingleVector(int max_length)
    : result_table_(max_length),
      value_table_(max_length),
      is_stored_table_(max_length) {}
template <typename Key, typename Result>
bool SingleVector<Key, Result>::IsStoredState(const Key &state) const {
  assert(IsValidState(state));
  return is_stored_table_[GetIndex(state)];
}

template <typename Key, typename Result>
float SingleVector<Key, Result>::GetOptimalValue(const Key &state) const {
  assert(IsValidState(state));
  return value_table_[GetIndex(state)];
}

template <typename Key, typename Result>
Result SingleVector<Key, Result>::GetOptimalResult(const Key &state) const {
  assert(IsValidState(state));
  return result_table_[GetIndex(state)];
}

template <typename Key, typename Result>
void SingleVector<Key, Result>::StoreOptimalResult(const Key &state,
                                                   Result opt_result,
                                                   float value) {
  assert(IsValidState(state));
  result_table_.at(GetIndex(state)) = opt_result;
  value_table_.at(GetIndex(state)) = value;
  is_stored_table_.at(GetIndex(state)) = true;
}

}  // namespace storage
}  // namespace genericdp
#endif  // _GENERICDP_SINGLE_VECTOR_H_
