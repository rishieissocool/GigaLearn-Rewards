class VersatileBallVelocityReward(RewardFunction):
def __init__(self):
        super().__init__()
        self.offensive_reward = VelocityBallToGoalReward()
        self.defensive_reward = VelocityBallDefense()

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        if (player.team_num == BLUE_TEAM and state.ball.position[1] < 0) or (
            player.team_num == ORANGE_TEAM and state.ball.position[1] > 0
        ):
            return self.defensive_reward.get_reward(player, state, previous_action)
        else:
            return self.offensive_reward.get_reward(player, state, previous_action)
