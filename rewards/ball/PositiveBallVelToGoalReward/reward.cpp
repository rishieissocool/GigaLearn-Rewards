    class PositiveBallVelToGoalReward : public Reward {

    public:
        VelocityBallToGoalReward rew;

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            return std::clamp(rew.GetReward(player, state, isFinal), 0.0f, 1.0f);
        }
    
    };
