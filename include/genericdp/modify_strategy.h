#ifndef _MODIFY_STRATEGY_H_
#define _MODIFY_STRATEGY_H_

namespace genericdp {

template <typename T> class ModifyStrategy {
public:
  virtual void Modify(T *state) const = 0;
};

} // namespace genericdptest

#endif // _MODIFY_STRATEGY_H_
