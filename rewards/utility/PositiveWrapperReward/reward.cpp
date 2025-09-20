    class PositiveWrapperReward : public Reward {

    public:
        Reward* rew;

        PositiveWrapperReward(Reward* base_reward) : rew(base_reward) {}

        virtual void Reset(const GameState& initialState) override {
            rew->Reset(initialState);
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = rew->GetReward(player, state, isFinal);
            return reward < 0.0f ? 0.0f : reward;
        }
    
    };
