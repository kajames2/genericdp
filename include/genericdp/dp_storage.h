#ifndef _GENERICDP_DP_STORAGE_H_
#define _GENERICDP_DP_STORAGE_H_

#include <memory>

#include "genericdp/dp_result.h"

namespace genericdp {
template <typename Key>
class DPStorage {
 public:
  virtual const DPResult<Key> &GetOptimalResult(const Key &state) const = 0;
  virtual bool IsTerminalState(const Key &state) const = 0;
  virtual bool IsStoredState(const Key &state) const = 0;
  virtual double GetOptimalValue(const Key &state) const = 0;
  virtual void StoreOptimalResult(const Key &state,
                                  DPResult<Key> opt_result) = 0;

  DPStorage() = default;
  DPStorage(const DPStorage &) = delete;
  DPStorage &operator=(const DPStorage &) = delete;
  virtual ~DPStorage() {}
};
}  // namespace genericdp
#endif  // _GENERICDP_DP_STORAGE_H_
