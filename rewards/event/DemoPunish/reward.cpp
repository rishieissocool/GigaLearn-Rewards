    class DemoPunish : public Reward {
    public:
        std::vector<bool> demo_statuses;

        DemoPunish() : demo_statuses(64, true) {}

        virtual void Reset(const GameState& initialState) override {
            demo_statuses.assign(64, true);
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            if (player.eventState.demoed && !demo_statuses[player.carId]) {
                reward = -1.0f;
            }
            demo_statuses[player.carId] = player.eventState.demoed;
            return reward;
        }
    };