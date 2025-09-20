    class MillennialKickoffReward : public Reward {

    public:
        bool closest_to_ball(const Player& player, const GameState& state) {
            float player_dist = player.pos.Dist(state.ball.pos);
            for (const auto& p : state.players) {
                if (p.team == player.team && p.carId != player.carId) {
                    float dist = p.pos.Dist(state.ball.pos);
                    if (dist < player_dist) {
                        return false;
                    }
                }
            }
            return true;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (state.ball.pos.x == 0.0f && state.ball.pos.y == 0.0f && closest_to_ball(player, state)) {
                return -1.0f;
            }
            return 0.0f;
        }
    
    };
