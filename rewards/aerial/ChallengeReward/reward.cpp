    class ChallengeReward : public Reward {

    public:
        float challenge_distance;

        ChallengeReward(float challenge_distance = 300.0f) : challenge_distance(challenge_distance) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (!player.isOnGround && player.pos.Dist(state.ball.pos) < challenge_distance) {
                for (const auto& p : state.players) {
                    if (p.team != player.team && p.pos.Dist(state.ball.pos) < challenge_distance) {
                        reward += 0.1f;
                        if (!player.has_flip) {
                            reward += 0.9f;
                        }
                        break;
                    }
                }
            }
            return reward;
        }
    
    };
