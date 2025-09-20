class DistanceReward(RewardFunction):
def __init__(self, dist_max=1000, max_reward=2):
        super().__init__()
        self.dist_max = dist_max

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        difference = state.ball.position - player.car_data.position
        distance = (
            math.sqrt(
                difference[0] * difference[0]
                + difference[1] * difference[1]
                + difference[2] * difference[2]
            )
            - 110
        )

        if distance > self.dist_max:
            return 0

        return 1 - (distance / self.dist_max)
