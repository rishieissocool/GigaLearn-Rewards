    class NaiveSpeedReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            return std::abs(player.vel.Length()) / 2300.0f;
        }
    
    };
