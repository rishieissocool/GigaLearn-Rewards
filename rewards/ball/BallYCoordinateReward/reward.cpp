    class BallYCoordinateReward : public Reward {

    public:
        float exponent;

        BallYCoordinateReward(float exponent = 1.0f) : exponent(exponent) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float y = (player.team == BLUE_TEAM) ? state.ball.pos.y : -state.ball.pos.y;
            return std::pow(y / (BACK_WALL_Y + BALL_RADIUS), exponent);
        }
    
    };
