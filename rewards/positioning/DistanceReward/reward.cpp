    class DistanceReward : public Reward {

    public:
        float dist_max;
        float max_reward;

        DistanceReward(float dist_max = 1000.0f, float max_reward = 2.0f)
            : dist_max(dist_max), max_reward(max_reward) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float distance = (state.ball.pos - player.pos).Length() - 110.0f;
            if (distance > dist_max) {
                return 0.0f;
            }
            return max_reward * (1.0f - (distance / dist_max));
        }
    
    };
