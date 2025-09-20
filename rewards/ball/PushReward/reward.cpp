    class PushReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec pos = (player.team == BLUE_TEAM) ? state.ball.pos : -state.ball.pos;
            if (pos.y > 0.0f) {
                float y_scale = pos.y / 5213.0f;
                if (std::abs(pos.x) > 800.0f) {
                    float x_scale = (std::abs(pos.x) / 4096.0f) * y_scale;
                    return y_scale - x_scale;
                }
                return y_scale;
            } else if (pos.y < 0.0f) {
                float y_scale = pos.y / 5213.0f;
                if (std::abs(pos.x) > 800.0f) {
                    float x_scale = (std::abs(pos.x) / 4096.0f) * std::abs(y_scale);
                    return y_scale + x_scale;
                }
                return y_scale;
            }
            return 0.0f;
        }
    
    };
