    class EventReward : public Reward {

    public:
        float goal, team_goal, concede, touch, shot, save, demo, boost_pickup;
        std::vector<float> last_registered_values;

        EventReward(float goal = 0.0f, float team_goal = 0.0f, float concede = 0.0f, float touch = 0.0f,
                    float shot = 0.0f, float save = 0.0f, float demo = 0.0f, float boost_pickup = 0.0f)
            : goal(goal), team_goal(team_goal), concede(concede), touch(touch),
              shot(shot), save(save), demo(demo), boost_pickup(boost_pickup) {}

        virtual void Reset(const GameState& initialState) override {
            last_registered_values.clear();
            for (const auto& player : initialState.players) {
                last_registered_values.push_back(extract_values(player, initialState));
            }
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float old_value = last_registered_values[player.carId];
            float new_value = extract_values(player, state);
            float diff = new_value - old_value;
            if (diff < 0) diff = 0.0f;
            last_registered_values[player.carId] = new_value;
            return diff * (player.team == BLUE_TEAM ? 1.0f : -1.0f);
        }

    private:
        float extract_values(const Player& player, const GameState& state) {
            int team_score = (player.team == BLUE_TEAM) ? state.blue_score : state.orange_score;
            int opponent_score = (player.team == BLUE_TEAM) ? state.orange_score : state.blue_score;
            return player.match_goals * goal +
                   team_score * team_goal +
                   opponent_score * concede +
                   player.ballTouchedStep * touch +
                   player.match_shots * shot +
                   player.match_saves * save +
                   player.match_demolishes * demo +
                   player.boost * boost_pickup;
        }
    
    };
