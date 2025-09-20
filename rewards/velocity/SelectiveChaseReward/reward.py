class SelectiveChaseReward(RewardFunction):
def __init__(self, distance_req: float = 500):
        super().__init__()
        self.vel_dir_reward = VelocityPlayerToBallReward()
        self.distance_requirement = distance_req

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        if (
            distance2D(player.car_data.position, state.ball.position)
            > self.distance_requirement
        ):
            return self.vel_dir_reward.get_reward(player, state, previous_action)
        return 0
