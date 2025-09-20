class SaveBoostReward(RewardFunction):
def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        return player.boost_amount * 0.01
