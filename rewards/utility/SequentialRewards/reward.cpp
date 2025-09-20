    class SequentialRewards : public Reward {

    public:
        std::vector<Reward*> rewards_list;
        std::vector<int> step_counts;
        int step_count;
        int step_index;

        SequentialRewards(const std::vector<Reward*>& rewards, const std::vector<int>& steps)
            : rewards_list(rewards), step_counts(steps), step_count(0), step_index(0) {}

        virtual void Reset(const GameState& initialState) override {
            for (auto& rew : rewards_list) {
                rew->Reset(initialState);
            }
            step_count = 0;
            step_index = 0;
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            if (step_index < step_counts.size() && step_count > step_counts[step_index]) {
                step_index++;
            }
            step_count++;
            return rewards_list[step_index]->GetReward(player, state, isFinal);
        }
    
    };
