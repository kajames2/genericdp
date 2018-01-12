#include "modify_strategy_set.h"
#include "modify_vector_iterator.h"
#include "simple_shock_modify_strategy.h"
#include "simple_dp_state.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class ModifyVectorIteratorTest : public ::testing::Test {
 public:
  ModifyVectorIteratorTest() {}

 protected:
  virtual void SetUp() {
    auto mod_strat_1_ = std::make_shared<genericdptest::SimpleShockModifyStrategy>(0, 0.6);
    auto mod_strat_2_ = std::make_shared<genericdptest::SimpleShockModifyStrategy>(-3, 0.4);
    shocks_ = genericdp::ModifyStrategySet<genericdptest::SimpleDPState>();
    shocks_.AddStrategy(mod_strat_1_);
    shocks_.AddStrategy(mod_strat_2_);

    state_ = std::make_unique<genericdptest::SimpleDPState>();
    state_->cash = 10;
    state_->period = 4;

    it_ = std::make_unique<genericdp::ModifyVectorIterator<genericdptest::SimpleDPState>>(*state_, shocks_);
  }
  
  std::unique_ptr<genericdp::ModifyVectorIterator<genericdptest::SimpleDPState>> it_;
  genericdp::ModifyStrategySet<genericdptest::SimpleDPState> shocks_;
  std::unique_ptr<genericdptest::SimpleDPState> state_;
};

TEST_F(ModifyVectorIteratorTest, IncrementTest) {
  genericdp::ModifyVectorIterator<genericdptest::SimpleDPState> &it = *it_;
  ASSERT_EQ(it->cash, 10);
  ASSERT_EQ(it->period, 4);
  ASSERT_DOUBLE_EQ(it->probability, 0.6);

  ++it;
  ASSERT_EQ(it->cash, 7);
  ASSERT_EQ(it->period, 4);
  ASSERT_DOUBLE_EQ(it->probability, 0.4);
}

TEST_F(ModifyVectorIteratorTest, FinishTest) {
  genericdp::ModifyVectorIterator<genericdptest::SimpleDPState> &it = *it_;
  ASSERT_TRUE(static_cast<bool>(it));
  ++it;
  ASSERT_TRUE(static_cast<bool>(it));
  ++it;
  ASSERT_FALSE(static_cast<bool>(it));
}
