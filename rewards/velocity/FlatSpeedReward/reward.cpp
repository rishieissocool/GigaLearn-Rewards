    class FlatSpeedReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            Vec flat_vel = player.vel;
            flat_vel.z = 0.0f;
            return std::abs(flat_vel.Length()) / 2300.0f;
        }
    
    };
