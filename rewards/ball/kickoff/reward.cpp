	class KickoffReward : public Reward {
	public:
		VelocityPlayerToBallReward velDirReward;
		SpeedReward velReward;
		bool boostPunish;
		int ticks;

		KickoffReward(bool boostPunish = true)
			: boostPunish(boostPunish), ticks(0) {
		}

		virtual void Reset(const GameState& initialState) {
			ticks = 0;
		}

		bool IsClosestToBall(const Player& player, const GameState& state) {
			float playerDist = player.pos.Dist(state.ball.pos);
			for (const auto& p : state.players) {
				if (p.carId != player.carId && p.team == player.team && !p.eventState.demoed) {
					float dist = p.pos.Dist(state.ball.pos);
					if (dist < playerDist) {
						return false;
					}
				}
			}
			return true;
		}

		virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
			float reward = 0.0f;
			if (fabs(state.ball.pos.x) < 0.01f && fabs(state.ball.pos.y) < 0.01f && IsClosestToBall(player, state)) {
				reward += velReward.GetReward(player, state, isFinal);
				reward += velDirReward.GetReward(player, state, isFinal);
			}
			ticks++;
			return reward;
		}
	};