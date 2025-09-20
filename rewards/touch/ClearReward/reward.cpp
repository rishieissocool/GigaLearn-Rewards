    class ClearReward : public Reward {

    public:
        Vec last_vel;

        virtual void Reset(const GameState& initialState) override {
            last_vel = Vec(0.0f, 0.0f, 0.0f);
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (player.ballTouchedStep) {
                float vel_difference = (last_vel - state.ball.vel).Length();
                reward = vel_difference / 4600.0f;
            }
            last_vel = state.ball.vel;
            return reward;
        }
    
    };
