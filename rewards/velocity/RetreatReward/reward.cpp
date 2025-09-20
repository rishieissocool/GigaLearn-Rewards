    class RetreatReward : public Reward {

    public:
        Vec defense_target;

        RetreatReward() : defense_target(BLUE_GOAL_BACK) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec ball = (player.team == BLUE_TEAM) ? state.ball.pos : -state.ball.pos;
            Vec pos = (player.team == BLUE_TEAM) ? player.pos : -player.pos;
            Vec vel = (player.team == BLUE_TEAM) ? player.vel : -player.vel;
            float reward = 0.0f;
            if (ball.y + 200.0f < pos.y) {
                Vec pos_diff = defense_target - pos;
                Vec norm_pos_diff = pos_diff.Normalized();
                Vec norm_vel = vel / CAR_MAX_SPEED;
                reward = norm_pos_diff.Dot(norm_vel);
            }
            return reward;
        }
    
    };
