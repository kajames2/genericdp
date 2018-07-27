#ifndef _GENERICDP_VALUE_CALCULATOR_H_
#define _GENERICDP_VALUE_CALCULATOR_H_

namespace genericdp {
template <class InState>
class ValueCalculator {
 public:
  explicit ValueCalculator(double discount_rate = 1)
      : discount_rate_(discount_rate) {}

  virtual double CalculateValue(double immediate_value,
                                double future_value) const {
    return immediate_value + discount_rate_ * future_value;
  }

  virtual double CalculateTerminalValue(const InState& term_state) const {
    return 0;
  }

  virtual ~ValueCalculator() {}

 private:
  double discount_rate_;
};

}  // namespace genericdp
#endif  // _GENERICDP_VALUE_CALCULATOR_H_
