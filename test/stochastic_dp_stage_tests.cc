#include "stochastic_dp_stage.h"
#include "modify_vector_iterator_factory.h"
#include "simple_dp_state.h"
#include "simple_shock_modify_strategy.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class StochasticDPStageTest : public ::testing::Test {
 public:
  StochasticDPStageTest() : stage_(nullptr) {}

 protected:
  virtual void SetUp() {
    auto mod_strat_1 = std::make_shared<genericdptest::SimpleShockModifyStrategy>(0, 0.6);
    auto mod_strat_2 = std::make_shared<genericdptest::SimpleShockModifyStrategy>(-3, 0.4);
    std::vector<std::shared_ptr<genericdp::ModifyStrategy<genericdptest::SimpleDPState>>> shocks;
    shocks.push_back(mod_strat_1);
    shocks.push_back(mod_strat_2);

    auto fact_ = std::make_unique<genericdp::ModifyVectorIteratorFactory<genericdptest::SimpleDPState>>(shocks);


    stage_ = genericdp::StochasticDPStage<genericdptest::SimpleDPState>(std::move(fact_));
    state_.cash = 10;
    state_.period = 4;

    state2_.cash = 0;
    state2_.period = 1;
  }
  genericdp::StochasticDPStage<genericdptest::SimpleDPState> stage_;
  genericdptest::SimpleDPState state_, state2_;
};

TEST_F(StochasticDPStageTest, Evaluate) {
  auto res = stage_.Evaluate(&state_);
  ASSERT_EQ((*res)[0].cash, 10);
  ASSERT_DOUBLE_EQ((*res)[0].probability, 0.6);
  ASSERT_EQ((*res)[1].cash, 7);
  ASSERT_DOUBLE_EQ((*res)[1].probability, 0.4);  
}
