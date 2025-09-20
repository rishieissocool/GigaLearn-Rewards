    class LandingRecoveryReward : public Reward {

    public:
        Vec up;

        LandingRecoveryReward() : up(0.0f, 0.0f, 1.0f) {}

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (!player.isOnGround && player.vel.z < 0.0f && player.pos.z > 250.0f) {
                Vec flattened_vel = player.vel;
                flattened_vel.z = 0.0f;
                flattened_vel = flattened_vel.Normalized();
                Vec forward = player.rotMat.forward;
                Vec flattened_forward = Vec(forward.x, forward.y, 0.0f).Normalized();
                reward += flattened_vel.Dot(flattened_forward);
                reward += up.Dot(player.rotMat.up);
                reward /= 2.0f;
            }
            return reward;
        }
    
    };
