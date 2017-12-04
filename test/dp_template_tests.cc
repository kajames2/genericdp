#include "decision_dp_stage.h"
#include "exogenous_dp_stage.h"
#include "simple_modify_strategy.h"
#include "simple_decision_iterator_factory.h"
#include "simple_dp_state.h"
#include "simple_storage.h"
#include "dp_template.h"
#include "value_strategy.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include <iostream>

class DPTemplateTest : public ::testing::Test {
 public:
  DPTemplateTest() {}

 protected:
  virtual void SetUp() {
    auto fact_ = std::make_unique<genericdptest::SimpleDecisionIteratorFactory>();
    auto dec_stage = std::make_unique<genericdp::DecisionDPStage<genericdptest::SimpleDPState>>(std::move(fact_));
    auto mod = std::make_shared<genericdptest::SimpleModifyStrategy>();
    auto ex_stage = std::make_unique<genericdp::ExogenousDPStage<genericdptest::SimpleDPState>>(mod);
    std::vector<std::unique_ptr<genericdp::DPStage<genericdptest::SimpleDPState>>> vec;
    vec.push_back(std::move(dec_stage));
    vec.push_back(std::move(ex_stage));
    auto val_strat = std::make_shared<genericdp::ValueStrategy<genericdptest::SimpleDPState>>();
    auto storage = std::make_unique<genericdptest::SimpleStorage>(3, 9);
    dp = std::make_unique<genericdp::DPTemplate<genericdptest::SimpleDPState>>(std::move(storage), std::move(vec), val_strat);

    state.period = 1;
    state.cash = 9;
  }
  std::unique_ptr<genericdp::DPTemplate<genericdptest::SimpleDPState>> dp;
  genericdptest::SimpleDPState state, state2;
};

TEST_F(DPTemplateTest, Evaluate) {
  auto res = dp->GetOptimalResult(state);
  ASSERT_DOUBLE_EQ(res.GetValue(), 3*(1-std::exp(-3)));
  ASSERT_EQ(res[0].investment, 3);
}
