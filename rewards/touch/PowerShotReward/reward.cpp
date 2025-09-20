    class PowerShotReward : public Reward {

    public:
        float min_change;
        Vec last_velocity;

        PowerShotReward(float min_change = 300.0f) : min_change(min_change), last_velocity(0.0f, 0.0f, 0.0f) {}

        virtual void Reset(const GameState& initialState) override {
            last_velocity = Vec(0.0f, 0.0f, 0.0f);
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            Vec cur_vel = Vec(state.ball.vel.x, state.ball.vel.y, 0.0f);
            if (player.ballTouchedStep) {
                float vel_change = (last_velocity - cur_vel).Length();
                if (vel_change > min_change) {
                    reward = vel_change / (2300.0f * 2.0f);
                }
            }
            last_velocity = cur_vel;
            return reward;
        }
    
    };
