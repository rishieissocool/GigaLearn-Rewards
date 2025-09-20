    class TouchBallReward : public Reward {

    public:
        float min_touch, min_height, min_distance, aerial_weight;
        bool air_reward, first_touch;

        TouchBallReward(float min_touch = 0.05f, float min_height = 170.0f, float min_distance = 300.0f,
                        float aerial_weight = 0.15f, bool air_reward = true, bool first_touch = false)
            : min_touch(min_touch), min_height(min_height), min_distance(min_distance),
              aerial_weight(aerial_weight), air_reward(air_reward), first_touch(first_touch) {}

        float get_closest_enemy_distance(const Player& player, const GameState& state) {
            float closest_dist = 50000.0f;
            for (const auto& p : state.players) {
                if (p.team != player.team) {
                    float dist = player.pos.Dist2D(p.pos);
                    if (dist < closest_dist) {
                        closest_dist = dist;
                    }
                }
            }
            return closest_dist;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (player.ballTouchedStep) {
                if (first_touch && state.ball.pos.x == 0.0f && state.ball.pos.y == 0.0f) {
                    reward += 5.0f;
                }
                if (state.ball.pos.z >= min_height && (min_distance == 0.0f || get_closest_enemy_distance(player, state) > min_distance)) {
                    reward += std::max(min_touch, std::pow(std::abs(state.ball.pos.z - BALL_RADIUS), aerial_weight) - 1.0f);
                }
                if (air_reward && !player.isOnGround) {
                    reward += player.has_flip ? 0.5f : 1.0f;
                }
            }
            return reward;
        }
    
    };
