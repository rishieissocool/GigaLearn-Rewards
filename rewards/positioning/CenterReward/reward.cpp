    class CenterReward : public Reward {

    public:
        float centered_distance;
        bool punish_area_exit;
        float non_participation_reward;
        bool centered;
        Vec goal_spot;

        CenterReward(float centered_distance = 1200.0f, bool punish_area_exit = false, float non_participation_reward = 0.0f)
            : centered_distance(centered_distance), punish_area_exit(punish_area_exit),
              non_participation_reward(non_participation_reward), centered(false), goal_spot(0.0f, 5120.0f, 0.0f) {}

        virtual void Reset(const GameState& initialState) override {
            centered = false;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec ball_loc = (player.team == BLUE_TEAM) ? state.ball.pos : -state.ball.pos;
            float ball_dist_2d = (goal_spot - ball_loc).Length2D();
            float reward = 0.0f;
            if (centered) {
                if (ball_dist_2d > centered_distance) {
                    centered = false;
                    if (punish_area_exit) {
                        reward -= 1.0f;
                    }
                }
            } else {
                if (ball_dist_2d < centered_distance) {
                    centered = true;
                    reward += (state.last_touch == player.carId) ? 1.0f : non_participation_reward;
                }
            }
            return reward;
        }
    
    };
