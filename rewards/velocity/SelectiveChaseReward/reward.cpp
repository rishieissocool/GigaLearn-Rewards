    class SelectiveChaseReward : public Reward {

    public:
        VelocityPlayerToBallReward vel_dir_reward;
        float distance_requirement;

        SelectiveChaseReward(float distance_req = 500.0f) : distance_requirement(distance_req) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (player.pos.Dist2D(state.ball.pos) > distance_requirement) {
                return vel_dir_reward.GetReward(player, state, isFinal);
            }
            return 0.0f;
        }
    
    };
