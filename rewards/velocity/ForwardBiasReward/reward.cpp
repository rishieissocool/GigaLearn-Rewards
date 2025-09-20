    class ForwardBiasReward : public Reward {

    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            return player.rotMat.forward.Dot(player.vel.Normalized());
        }
    
    };
