    class GroundedReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            return player.isOnGround ? 1.0f : 0.0f;
        }
    
    };
