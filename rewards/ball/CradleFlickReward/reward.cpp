    class CradleFlickReward : public Reward {

    public:
        float min_distance, max_vel_diff;
        bool training;
        CradleReward cradle_reward;

        CradleFlickReward(float minimum_barrier = 400.0f, float max_vel_diff = 400.0f, bool training = true)
            : min_distance(minimum_barrier), max_vel_diff(max_vel_diff), training(training), cradle_reward(0.0f) {}

        virtual void Reset(const GameState& initialState) override {
            cradle_reward.Reset(initialState);
        }

        bool stable_carry(const Player& player, const GameState& state) {
            if (BALL_RADIUS + 20.0f < state.ball.pos.z && state.ball.pos.z < BALL_RADIUS + 80.0f) {
                return (player.vel - state.ball.vel).Length() <= max_vel_diff;
            }
            return false;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = cradle_reward.GetReward(player, state, isFinal) * 0.5f;
            if (reward > 0.0f) {
                if (!training) {
                    reward = 0.0f;
                }
                bool stable = stable_carry(player, state);
                bool challenged = false;
                for (const auto& p : state.players) {
                    if (p.team != player.team && p.pos.Dist(state.ball.pos) < min_distance) {
                        challenged = true;
                        break;
                    }
                }
                if (challenged) {
                    if (stable) {
                        if (player.isOnGround) {
                            return reward - 0.5f;
                        } else {
                            return player.has_flip ? reward + 2.0f : reward + 5.0f;
                        }
                    }
                } else if (stable) {
                    return reward + 1.0f;
                }
            }
            return reward;
        }
    
    };
