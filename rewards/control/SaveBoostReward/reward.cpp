    class SaveBoostReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            return player.boost * 0.01f;
        }
    
    };
