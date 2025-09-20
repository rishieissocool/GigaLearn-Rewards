class ForwardBiasReward(RewardFunction):
def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        return player.car_data.forward().dot(normalize(player.car_data.linear_velocity))
