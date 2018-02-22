#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "genericdp/dp_state.h"
#include "genericdp/modify_strategy_set.h"
#include "genericdp/modify_vector_iterator.h"
#include "test/simple_shock_modify_strategy.h"
#include "test/simple_state.h"

class ModifyVectorIteratorTest : public ::testing::Test {
 public:
  ModifyVectorIteratorTest() {}

 protected:
  virtual void SetUp() {
    auto mod_strat_1_ =
        std::make_shared<genericdptest::SimpleShockModifyStrategy>(0, 0.6);
    auto mod_strat_2_ =
        std::make_shared<genericdptest::SimpleShockModifyStrategy>(-3, 0.4);
    shocks_ = genericdp::ModifyStrategySet<genericdptest::SimpleState>();
    shocks_.AddStrategy(mod_strat_1_);
    shocks_.AddStrategy(mod_strat_2_);

    state_.cash = 10;
    state_.period = 4;

    it_ = std::make_unique<
        genericdp::ModifyVectorIterator<genericdptest::SimpleState>>(
        genericdp::DPState<genericdptest::SimpleState>(state_), shocks_);
  }

  std::unique_ptr<genericdp::ModifyVectorIterator<genericdptest::SimpleState>>
      it_;
  genericdp::ModifyStrategySet<genericdptest::SimpleState> shocks_;
  genericdptest::SimpleState state_;
};

TEST_F(ModifyVectorIteratorTest, IncrementTest) {
  genericdp::ModifyVectorIterator<genericdptest::SimpleState> &it = *it_;
  ASSERT_EQ(it->domain.cash, 10);
  ASSERT_EQ(it->domain.period, 4);
  ASSERT_DOUBLE_EQ(it->probability, 0.6);

  ++it;
  ASSERT_EQ(it->domain.cash, 7);
  ASSERT_EQ(it->domain.period, 4);
  ASSERT_DOUBLE_EQ(it->probability, 0.4);
}

TEST_F(ModifyVectorIteratorTest, FinishTest) {
  genericdp::ModifyVectorIterator<genericdptest::SimpleState> &it = *it_;
  ASSERT_TRUE(static_cast<bool>(it));
  ++it;
  ASSERT_TRUE(static_cast<bool>(it));
  ++it;
  ASSERT_FALSE(static_cast<bool>(it));
}
