#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "genericdp/stage_exogenous.h"
#include "test/simple_modify_strategy.h"
#include "test/simple_state.h"

class StageExogenousTest : public ::testing::Test {
 public:
  StageExogenousTest() : mod_strat_() {}

 protected:
  virtual void SetUp() {
    mod_strat_ = std::make_shared<genericdptest::SimpleModifyStrategy>();
    stage_ =
        std::make_unique<genericdp::StageExogenous<genericdptest::SimpleState>>(
            mod_strat_);

    genericdptest::SimpleState state;
    state.cash = 10;
    state.period = 4;
    state.investment = 1;
    dp_state_.domain = state;
  }
  std::shared_ptr<genericdptest::SimpleModifyStrategy> mod_strat_;
  std::unique_ptr<genericdp::StageExogenous<genericdptest::SimpleState>> stage_;
  genericdp::DPState<genericdptest::SimpleState> dp_state_;
};

TEST_F(StageExogenousTest, Evaluate) {
  stage_->Evaluate(&dp_state_);
  ASSERT_EQ(5, dp_state_.domain.period);
  ASSERT_DOUBLE_EQ(1 - std::exp(-1), dp_state_.immediate_value);
  ASSERT_DOUBLE_EQ(0, dp_state_.future_value);
}
