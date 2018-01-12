#ifndef _SIMPLE_STORAGE_H_
#define _SIMPLE_STORAGE_H_

#include "simple_dp_state.h"
#include "single_vector_dp_storage.h"

namespace genericdptest {
class SimpleStorage : public genericdp::SingleVectorDPStorage<SimpleDPState> {
public:
  SimpleStorage(int max_periods, int max_cash)
      : genericdp::SingleVectorDPStorage<SimpleDPState>(max_periods *
                                                        (max_cash + 1)),
        max_periods_(max_periods), max_cash_(max_cash) {}
  virtual bool IsTerminalState(const SimpleDPState &state) const override {
    return state.period == max_periods_ + 1;
  }

protected:
  virtual bool IsValidState(const SimpleDPState &state) const override {
    return state.period >= 0 && state.period <= max_periods_ &&
           state.cash >= 0 && state.cash <= max_cash_;
  }
  virtual int GetIndex(const SimpleDPState &state) const override {
    return (state.period - 1) * (max_cash_ + 1) + state.cash;
  }

private:
  int max_periods_;
  int max_cash_;
};

} // namespace genericdptest
#endif // _SIMPLE_STORAGE_H_
