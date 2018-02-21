#ifndef _GENERICDP_VALUE_STRATEGY_H_
#define _GENERICDP_VALUE_STRATEGY_H_

namespace genericdp {
template <class T>
class ValueStrategy {
 public:
  ValueStrategy(double discount_rate = 1) : discount_rate_(discount_rate) {}

  virtual double CalculateValue(double current_value,
                                double future_value) const {
    return current_value + discount_rate_ * future_value;
  }

  virtual double CalculateTerminalValue(const T& term_state) const { return 0; }

  ValueStrategy(const ValueStrategy&) = delete;
  ValueStrategy& operator=(const ValueStrategy&) = delete;
  virtual ~ValueStrategy() {}

 private:
  double discount_rate_;
};

}  // namespace genericdp
#endif  // _GENERICDP_VALUE_STRATEGY_H_
