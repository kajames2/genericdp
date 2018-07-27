#ifndef _GENERICDP_STORAGE_H_
#define _GENERICDP_STORAGE_H_

#include <memory>

namespace genericdp {
template <typename Key, typename Result>
class Storage {
 public:
  virtual Result GetOptimalResult(const Key &state) const = 0;
  virtual bool IsTerminalState(const Key &state) const = 0;
  virtual bool IsStoredState(const Key &state) const = 0;
  virtual float GetOptimalValue(const Key &state) const = 0;
  virtual void StoreOptimalResult(const Key &state, Result opt_result,
                                  float value) = 0;

  Storage() = default;
  Storage(const Storage &) = delete;
  Storage &operator=(const Storage &) = delete;
  virtual ~Storage() {}
};
}  // namespace genericdp
#endif  // _GENERICDP_STORAGE_H_
