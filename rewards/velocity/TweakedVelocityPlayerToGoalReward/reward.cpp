    class TweakedVelocityPlayerToGoalReward : public Reward {

    public:
        float max_leeway, default_power;

        TweakedVelocityPlayerToGoalReward(float max_leeway = 100.0f, float default_power = 0.0f)
            : max_leeway(max_leeway), default_power(default_power) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec ball_pos = (player.team == BLUE_TEAM) ? state.ball.pos : -state.ball.pos;
            Vec player_pos = (player.team == BLUE_TEAM) ? player.pos : -player.pos;
            Vec player_goal = (player.team == BLUE_TEAM) ? BLUE_GOAL_BACK : ORANGE_GOAL_BACK;
            Vec diff = player_pos - ball_pos;
            if (diff.y < max_leeway) {
                return 0.0f;
            }
            Vec direction = (player_goal - player_pos).Normalized();
            Vec vel = player.vel / CAR_MAX_SPEED;
            return direction.Dot(vel);
        }
    
    };
