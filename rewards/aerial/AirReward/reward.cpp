    class AirReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (!player.isOnGround) {
                return player.has_flip ? 0.5f : 1.0f;
            }
            return 0.0f;
        }
    
    };
