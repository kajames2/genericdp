#ifndef _GENERICDP_RESULT_H_
#define _GENERICDP_RESULT_H_

#include "genericdp/valuation.h"

namespace genericdp {

template <typename State, typename Policy>
struct Result {
  Valuation valuation;
  State state;
  Policy policy;
};

template <typename State, typename Policy>
std::ostream& operator<<(std::ostream& out, const Result<State, Policy>& res) {
  return out << res.state << "," << res.policy << "," << res.valuation;
}

}  // namespace genericdp

#endif  // _GENERICDP_RESULT_H_
