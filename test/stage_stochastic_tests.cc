#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "genericdp/modify_strategy_set.h"
#include "genericdp/modify_vector_iterator_factory.h"
#include "genericdp/stage_stochastic.h"
#include "test/simple_shock_modify_strategy.h"
#include "test/simple_state.h"

class StageStochasticTest : public ::testing::Test {
 public:
  StageStochasticTest() : stage_(nullptr) {}

 protected:
  virtual void SetUp() {
    auto mod_strat_1 =
        std::make_shared<const genericdptest::SimpleShockModifyStrategy>(0,
                                                                         0.6);
    auto mod_strat_2 =
        std::make_shared<const genericdptest::SimpleShockModifyStrategy>(-3,
                                                                         0.4);
    genericdp::ModifyStrategySet<genericdptest::SimpleState> shocks;
    shocks.AddStrategy(mod_strat_1);
    shocks.AddStrategy(mod_strat_2);

    auto fact_ = std::make_unique<
        genericdp::ModifyVectorIteratorFactory<genericdptest::SimpleState>>(
        shocks);

    genericdptest::SimpleState state;
    stage_ = std::make_unique<
        genericdp::StageStochastic<genericdptest::SimpleState>>(
        std::move(fact_));
    state.cash = 10;
    state.period = 4;
    dp_state_.domain = state;
  }
  std::unique_ptr<genericdp::StageStochastic<genericdptest::SimpleState>>
      stage_;
  genericdp::DPState<genericdptest::SimpleState> dp_state_;
};

TEST_F(StageStochasticTest, Evaluate) {
  auto res = stage_->Evaluate(&dp_state_);
  ASSERT_EQ(res[0].domain.cash, 10);
  ASSERT_DOUBLE_EQ(res[0].probability, 0.6);
  ASSERT_EQ(res[1].domain.cash, 7);
  ASSERT_DOUBLE_EQ(res[1].probability, 0.4);
}
