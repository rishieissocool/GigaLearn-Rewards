    class JumpTouchReward : public Reward {

    public:
        float min_height, max_height, range;

        JumpTouchReward(float min_height = 92.75f)
            : min_height(min_height), max_height(2044.0f - 92.75f), range(max_height - min_height) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (player.ballTouchedStep && !player.isOnGround && state.ball.pos.z >= min_height) {
                return (state.ball.pos.z - min_height) / range;
            }
            return 0.0f;
        }
    
    };
