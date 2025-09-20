class PositivePlayerVelToBallReward(RewardFunction):
def __init__(self):
        super().__init__()
        self.rew = VelocityPlayerToBallReward()

    def reset(self, initial_state: GameState):
        self.rew.reset(initial_state)

    def get_reward(
            self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        return clamp(1, 0, self.rew.get_reward(player, state, previous_action))
