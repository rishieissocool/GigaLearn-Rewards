    class StarterReward : public Reward {

    public:
        EventReward event_reward;
        ClearReward touch_vel_change;
        VelocityBallToGoalReward vel_ball_to_goal;
        VelocityPlayerToBallReward vel_player_to_ball;
        JumpTouchReward jump_touch;
        KickoffReward kickoff;
        std::vector<float> weights;

        StarterReward()
            : event_reward(0.0f, 10.0f, -10.0f, 0.0f, 0.0f, 0.0f, 10.0f / 3.0f, 0.0f),
              jump_touch(120.0f), kickoff(false),
              weights({1.0f, 1.5f, 0.075f, 0.075f, 2.0f, 0.1f}) {}

        virtual void Reset(const GameState& initialState) override {
            event_reward.Reset(initialState);
            touch_vel_change.Reset(initialState);
            vel_ball_to_goal.Reset(initialState);
            vel_player_to_ball.Reset(initialState);
            jump_touch.Reset(initialState);
            kickoff.Reset(initialState);
        }

        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float reward = 0.0f;
            reward += event_reward.GetReward(player, state, isFinal) * weights[0];
            reward += touch_vel_change.GetReward(player, state, isFinal) * weights[1];
            reward += vel_ball_to_goal.GetReward(player, state, isFinal) * weights[2];
            reward += vel_player_to_ball.GetReward(player, state, isFinal) * weights[3];
            reward += jump_touch.GetReward(player, state, isFinal) * weights[4];
            reward += kickoff.GetReward(player, state, isFinal) * weights[5];
            return reward;
        }
    
    };
