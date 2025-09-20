    class SpeedReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            float car_speed = player.vel.Length();
            float car_dir = player.rotMat.forward.Dot(player.vel) >= 0 ? 1.0f : -1.0f;
            car_speed *= car_dir / 2300.0f;
            return std::min(car_speed, 1.0f);
        }
    
    };
