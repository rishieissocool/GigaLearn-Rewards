    class TouchBallTweakedReward : public Reward {

    public:
        float min_touch, min_height, min_distance, aerial_weight;
        bool air_reward, first_touch;
        Vec last_velocity;

        TouchBallTweakedReward(float min_touch = 0.05f, float min_height = 170.0f, float min_distance = 300.0f,
                               float aerial_weight = 0.15f, bool air_reward = true, bool first_touch = false)
            : min_touch(min_touch), min_height(min_height), min_distance(min_distance), aerial_weight(aerial_weight),
              air_reward(air_reward), first_touch(first_touch), last_velocity(0.0f, 0.0f, 0.0f) {}

        virtual void Reset(const GameState& initialState) override {
            last_velocity = Vec(0.0f, 0.0f, 0.0f);
        }

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
            Vec current_vel = state.ball.vel;
            if (player.ballTouchedStep) {
                if (state.ball.pos.z >= min_height || (state.ball.pos.z >= BALL_RADIUS + 20.0f &&
                    (min_distance == 0.0f || get_closest_enemy_distance(player, state) > min_distance))) {
                    reward += std::max(min_touch, std::pow(std::abs(state.ball.pos.z - BALL_RADIUS), aerial_weight) - 1.0f);
                    reward += (last_velocity - current_vel).Length() / 2300.0f;
                }
                if (air_reward && !player.isOnGround) {
                    reward += 0.5f;
                    if (!player.has_flip) {
                        reward += 0.5f;
                    }
                }
            }
            last_velocity = current_vel;
            return reward;
        }
    
    };
