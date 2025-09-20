    class LavaFloorReward : public Reward {
    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (player.isOnGround && player.pos.z < 50.0f) {
                return -1.0f;
            }
            return 0.0f;
        }
    };