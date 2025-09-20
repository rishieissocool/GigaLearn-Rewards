    class ThreeManRewards : public Reward {

    public:
        float min_spacing;
        VelocityBallToGoalReward vel_reward;
        KickoffReward kor;

        ThreeManRewards(float min_spacing = 1500.0f) : min_spacing(min_spacing) {}

        float spacing_reward(const Player& player, const GameState& state, int role) {
            float reward = 0.0f;
            if (role != 0) {
                for (const auto& p : state.players) {
                    if (p.team == player.team && p.carId != player.carId && !p.eventState.demoed) {
                        float separation = player.pos.Dist(p.pos);
                        if (separation < min_spacing) {
                            reward -= 1.0f - (separation / min_spacing);
                        }
                    }
                }
            }
            return reward;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            std::vector<std::pair<float, int>> player_distances;
            for (const auto& p : state.players) {
                if (p.team == player.team) {
                    player_distances.emplace_back(p.pos.Dist(state.ball.pos), p.carId);
                }
            }
            std::sort(player_distances.begin(), player_distances.end());
            int role = 0;
            for (size_t i = 0; i < player_distances.size(); ++i) {
                if (player_distances[i].second == player.carId) {
                    role = i;
                    break;
                }
            }
            float reward = spacing_reward(player, state, role);
            if (role == 1) {
                reward += vel_reward.GetReward(player, state, isFinal);
                reward += kor.GetReward(player, state, isFinal);
            }
            return reward;
        }
    
    };
