    class HeightTouchReward : public Reward {

    public:
        float min_height, exp, cooperation_dist;

        HeightTouchReward(float min_height = 92.0f, float exp = 0.2f, float cooperation_dist = 0.0f)
            : min_height(min_height), exp(exp), cooperation_dist(cooperation_dist) {}

        bool cooperation_detector(const Player& player, const GameState& state) {
            for (const auto& p : state.players) {
                if (p.carId != player.carId && player.pos.Dist(p.pos) < cooperation_dist) {
                    return true;
                }
            }
            return false;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (player.ballTouchedStep) {
                if (state.ball.pos.z >= min_height) {
                    if (!player.isOnGround || cooperation_dist < 90.0f || !cooperation_detector(player, state)) {
                        if (player.isOnGround) {
                            reward += std::pow(std::clamp(state.ball.pos.z - 92.0f, 0.0001f, 5000.0f), exp);
                        } else {
                            reward += std::pow(std::clamp(state.ball.pos.z, 1.0f, 500.0f), exp * 2.0f);
                        }
                    }
                } else if (!player.isOnGround) {
                    reward += 1.0f;
                }
            }
            return reward;
        }
    
    };
