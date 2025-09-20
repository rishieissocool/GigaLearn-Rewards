    class VersatileBallVelocityReward : public Reward {

    public:
        VelocityBallToGoalReward offensive_reward;
        VelocityBallDefense defensive_reward;

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            bool is_defensive = (player.team == BLUE_TEAM && state.ball.pos.y < 0.0f) ||
                                (player.team == ORANGE_TEAM && state.ball.pos.y > 0.0f);
            return is_defensive ? defensive_reward.GetReward(player, state, isFinal)
                               : offensive_reward.GetReward(player, state, isFinal);
        }
    
    };
