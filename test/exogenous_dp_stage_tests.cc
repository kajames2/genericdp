#include "exogenous_dp_stage.h"
#include "simple_modify_strategy.h"
#include "simple_dp_state.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class ExogenousDPStageTest : public ::testing::Test {
 public:
  ExogenousDPStageTest() : mod_strat_() {}

 protected:
  virtual void SetUp() {
    mod_strat_ = std::make_shared<genericdptest::SimpleModifyStrategy>();
    stage_ = std::make_unique<genericdp::ExogenousDPStage<genericdptest::SimpleDPState>>(mod_strat_);
    state_ = std::make_unique<genericdptest::SimpleDPState>();
    state_->cash = 10;
    state_->period = 4;
  }
  std::shared_ptr<genericdptest::SimpleModifyStrategy> mod_strat_;
  std::unique_ptr<genericdp::ExogenousDPStage<genericdptest::SimpleDPState>> stage_;
  std::unique_ptr<genericdptest::SimpleDPState> state_;
};

TEST_F(ExogenousDPStageTest, Evaluate) {
  state_->investment = 1;
  stage_->Evaluate(state_.get());
  ASSERT_EQ(5, state_->period);
  ASSERT_DOUBLE_EQ(1-std::exp(-1), state_->immediate_value);
  ASSERT_DOUBLE_EQ(0, state_->future_value);
}
