    class CradleReward : public Reward {

    public:
        float min_distance;

        CradleReward(float minimum_barrier = 200.0f) : min_distance(minimum_barrier) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (player.pos.z < state.ball.pos.z && BALL_RADIUS + 20.0f < state.ball.pos.z &&
                state.ball.pos.z < BALL_RADIUS + 200.0f && player.pos.Dist2D(state.ball.pos) <= 170.0f) {
                if (std::abs(state.ball.pos.x) < 3946.0f && std::abs(state.ball.pos.y) < 4970.0f) {
                    if (min_distance > 0.0f) {
                        for (const auto& p : state.players) {
                            if (p.team != player.team && p.pos.Dist(state.ball.pos) < min_distance) {
                                return 0.0f;
                            }
                        }
                    }
                    return 1.0f;
                }
            }
            return 0.0f;
        }
    
    };
