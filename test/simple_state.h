#ifndef _SIMPLE_STATE_H_
#define _SIMPLE_STATE_H_

namespace genericdptest {

class SimpleState {
 public:
  SimpleState() : investment(0), period(0), cash(0) {}
  int investment;
  int period;
  int cash;
};
}  // namespace genericdptest
#endif  // _SIMPLE_STATE_H_
