    class TeamSpacingReward : public Reward {

    public:
        float min_spacing;

        TeamSpacingReward(float min_spacing = 1000.0f)
            : min_spacing(std::max(0.0000001f, min_spacing)) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (player.eventState.demoed) {
                return reward;
            }
            for (const auto& p : state.players) {
                if (p.carId != player.carId && p.team == player.team && !p.eventState.demoed) {
                    float separation = player.pos.Dist(p.pos);
                    if (separation < min_spacing) {
                        reward -= 1.0f - (separation / min_spacing);
                    }
                }
            }
            return reward;
        }
    
    };
