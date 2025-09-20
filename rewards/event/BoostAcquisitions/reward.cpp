    class BoostAcquisitions : public Reward {
    public:
        float boost_reserves;

        BoostAcquisitions() : boost_reserves(1.0f) {}

        virtual void Reset(const GameState& initialState) override {
            boost_reserves = 1.0f;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float boost_gain = player.boost - boost_reserves;
            boost_reserves = player.boost;
            return boost_gain > 0 ? boost_gain : 0.0f;
        }
    };