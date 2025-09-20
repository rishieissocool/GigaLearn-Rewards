    class ModifiedTouchReward : public Reward {

    public:
        PowerShotReward psr;
        float min_height, height_cap, vel_scale, touch_scale, jump_scale;
        bool jump_reward;
        int tick_count, tick_min;

        ModifiedTouchReward(float min_change = 300.0f, float min_height = 200.0f, float vel_scale = 1.0f,
                           float touch_scale = 1.0f, bool jump_reward = false, float jump_scale = 0.1f, int tick_min = 0)
            : psr(min_change), min_height(min_height), height_cap(2044.0f - 92.75f), vel_scale(vel_scale),
              touch_scale(touch_scale), jump_reward(jump_reward), jump_scale(jump_scale), tick_count(0), tick_min(tick_min) {}

        virtual void Reset(const GameState& initialState) override {
            psr.Reset(initialState);
            tick_count = 0;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            float psr_val = psr.GetReward(player, state, isFinal);
            if (player.ballTouchedStep) {
                if (tick_count <= 0) {
                    tick_count = tick_min;
                    reward += std::abs(psr_val * vel_scale);
                    if (!player.isOnGround) {
                        if (jump_reward) {
                            reward += jump_scale;
                            if (!player.has_flip) {
                                reward += jump_scale;
                            }
                        }
                        if (state.ball.pos.z > min_height) {
                            reward += std::abs((state.ball.pos.z / height_cap) * touch_scale);
                        }
                    }
                } else {
                    tick_count--;
                }
            } else {
                tick_count--;
            }
            return reward;
        }
    
    };
