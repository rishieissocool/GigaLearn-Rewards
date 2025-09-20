    class DefenderReward : public Reward {

    public:
        int enemy_goals;

        DefenderReward() : enemy_goals(0) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            int e_score = (player.team == BLUE_TEAM) ? state.orange_score : state.blue_score;
            Vec defend_loc = (player.team == BLUE_TEAM) ? BLUE_GOAL_CENTER : ORANGE_GOAL_CENTER;
            if (e_score > enemy_goals) {
                enemy_goals = e_score;
                float dist = player.pos.Dist2D(defend_loc);
                if (dist > 900.0f) {
                    reward -= std::clamp(dist / 10000.0f, 0.0f, 1.0f);
                }
            }
            return reward;
        }
    
    };
