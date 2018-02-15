#include "stage_decision.h"
#include "stage_exogenous.h"
#include "simple_modify_strategy.h"
#include "simple_decision_iterator_factory.h"
#include "simple_state.h"
#include "simple_storage.h"
#include "dp.h"
#include "value_strategy.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class DPTest : public ::testing::Test {
 public:
  DPTest() {}

 protected:
  virtual void SetUp() {
    auto fact_ = std::make_unique<genericdptest::SimpleDecisionIteratorFactory>();
    auto dec_stage = std::make_unique<genericdp::StageDecision<genericdptest::SimpleState>>(std::move(fact_));
    auto mod = std::make_shared<genericdptest::SimpleModifyStrategy>();
    auto ex_stage = std::make_unique<genericdp::StageExogenous<genericdptest::SimpleState>>(mod);
    std::vector<std::unique_ptr<genericdp::Stage<genericdptest::SimpleState>>> vec;
    vec.push_back(std::move(dec_stage));
    vec.push_back(std::move(ex_stage));
    auto val_strat = std::make_shared<genericdp::ValueStrategy<genericdptest::SimpleState>>();
    auto storage = std::make_unique<genericdptest::SimpleStorage>(3, 9);
    dp = std::make_unique<genericdp::DP<genericdptest::SimpleState>>(std::move(storage), std::move(vec), val_strat);

    state.period = 1;
    state.cash = 9;
  }
  std::unique_ptr<genericdp::DP<genericdptest::SimpleState>> dp;
  genericdptest::SimpleState state, state2;
};

TEST_F(DPTest, Evaluate) {
  auto res = dp->GetOptimalResult(state);
  ASSERT_DOUBLE_EQ(res.GetValue(), 3*(1-std::exp(-3)));
  ASSERT_EQ(res[0].domain.investment, 3);
}
