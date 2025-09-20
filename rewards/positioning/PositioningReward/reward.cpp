    class PositioningReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec ball = (player.team == BLUE_TEAM) ? state.ball.pos : -state.ball.pos;
            Vec pos = (player.team == BLUE_TEAM) ? player.pos : -player.pos;
            float reward = 0.0f;
            if (ball.y < pos.y) {
                float diff = ball.y - pos.y;
                reward = -std::clamp(std::abs(diff) / 5000.0f, 0.0f, 1.0f);
            }
            return reward;
        }
    
    };
