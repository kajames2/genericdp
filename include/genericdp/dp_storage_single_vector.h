#ifndef _DP_STORAGE_SINGLE_VECTOR_H_
#define _DP_STORAGE_SINGLE_VECTOR_H_

#include "dp_result.h"
#include "dp_storage.h"
#include <memory>
#include <vector>

namespace genericdp {
template <typename Key> class DPStorageSingleVector : public DPStorage<Key> {
public:
  const DPResult<Key> &GetOptimalResult(const Key &state) const;
  virtual bool IsTerminalState(const Key &state) const = 0;
  bool IsStoredState(const Key &state) const;
  double GetOptimalValue(const Key &state) const;
  void StoreOptimalResult(const Key &state, DPResult<Key> opt_result);

  DPStorageSingleVector() = default;
  explicit DPStorageSingleVector(int max_length);
  DPStorageSingleVector(const DPStorageSingleVector &) = delete;
  DPStorageSingleVector &operator=(const DPStorageSingleVector &) = delete;
  virtual ~DPStorageSingleVector() {}

protected:
  virtual bool IsValidState(const Key &state) const = 0;
  virtual int GetIndex(const Key &state) const = 0;

  std::vector<DPResult<Key>> result_table_;
  std::vector<double> value_table_;
  std::vector<bool> is_stored_table_;
};

template <typename Key>
DPStorageSingleVector<Key>::DPStorageSingleVector(int max_length)
    : result_table_(max_length), value_table_(max_length),
      is_stored_table_(max_length) {
  
}
template <typename Key>
bool DPStorageSingleVector<Key>::IsStoredState(const Key &state) const {
  return is_stored_table_.at(GetIndex(state));
}

template <typename Key>
double DPStorageSingleVector<Key>::GetOptimalValue(const Key &state) const {
  return value_table_.at(GetIndex(state));
}

template <typename Key>
const DPResult<Key> &
DPStorageSingleVector<Key>::GetOptimalResult(const Key &state) const {
  return result_table_.at(GetIndex(state));
}

template <typename Key>
void DPStorageSingleVector<Key>::StoreOptimalResult(const Key &state,
                                                    DPResult<Key> opt_result) {
  result_table_.at(GetIndex(state)) = opt_result;
  value_table_.at(GetIndex(state)) = opt_result.GetValue();
  is_stored_table_.at(GetIndex(state)) = true;
}

} // namespace genericdp
#endif // _DP_STORAGE_SINGLE_VECTOR_H_
