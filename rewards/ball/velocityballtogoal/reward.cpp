    class VelocityBallToGoalReward : public Reward {
    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec ball_pos = (player.team == 0) ? state.ball.pos : -state.ball.pos;
            Vec goal_pos = (player.team == 0) ? Vec(0.0f, 6000.0f, 321.3875f) : Vec(0.0f, -6000.0f, 321.3875f);
            Vec pos_diff = ball_pos - goal_pos;
            Vec norm_pos_diff = pos_diff.Normalized();
            Vec vel = state.ball.vel / 6000.0f;
            return norm_pos_diff.Dot(vel);
        }
    };