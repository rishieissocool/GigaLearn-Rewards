    class VelocityPlayerToBallReward : public Reward {

    public:
        bool use_scalar_projection;

        VelocityPlayerToBallReward(bool use_scalar_projection = false)
            : use_scalar_projection(use_scalar_projection) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec pos_diff = state.ball.pos - player.pos;
            Vec norm_pos_diff = pos_diff.Normalized();
            Vec norm_vel = player.vel / CAR_MAX_SPEED;
            return norm_pos_diff.Dot(norm_vel);
        }
    
    };
