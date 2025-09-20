class CradleReward(RewardFunction):
def __init__(self, minimum_barrier: float = 200):
        super().__init__()
        self.min_distance = minimum_barrier

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        if (
            player.car_data.position[2] < state.ball.position[2]
            and (BALL_RADIUS + 20 < state.ball.position[2] < BALL_RADIUS + 200)
            and distance2D(player.car_data.position, state.ball.position) <= 170
        ):
            if (
                abs(state.ball.position[0]) < 3946
                and abs(state.ball.position[1]) < 4970
            ):  # side and back wall values - 150
                if self.min_distance > 0:
                    for _player in state.players:
                        if (
                            _player.team_num != player.team_num
                            and distance(_player.car_data.position, state.ball.position)
                            < self.min_distance
                        ):
                            return 0

                return 1

        return 0
