class KickoffReward(RewardFunction):
    def __init__(self, boost_punish=False):
        super().__init__()
        self.boost_punish = boost_punish

    def reset(self, initial_state: GameState):
        pass

    def get_reward(self, player: PlayerData, state: GameState, previous_action: np.ndarray) -> float:
        if state.ball.position[0] == 0 and state.ball.position[1] == 0:
            if self.boost_punish:
                return -player.boost / 100
            return 0
        return 0