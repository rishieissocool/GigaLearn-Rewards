class CradleFlickReward(RewardFunction):
def __init__(
        self,
        minimum_barrier: float = 400,
        max_vel_diff: float = 400,
        training: bool = True,
    ):
        super().__init__()
        self.min_distance = minimum_barrier
        self.max_vel_diff = max_vel_diff
        self.training = training
        self.cradle_reward = CradleReward(minimum_barrier=0)

    def reset(self, initial_state: GameState):
        self.cradle_reward.reset(initial_state)

    def stable_carry(self, player: PlayerData, state: GameState) -> bool:
        if BALL_RADIUS + 20 < state.ball.position[2] < BALL_RADIUS + 80:
            if (
                abs(
                    np.linalg.norm(
                        player.car_data.linear_velocity - state.ball.linear_velocity
                    )
                )
                <= self.max_vel_diff
            ):
                return True
        return False

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = self.cradle_reward.get_reward(player, state, previous_action) * 0.5
        if reward > 0:
            if not self.training:
                reward = 0
            stable = self.stable_carry(player, state)
            challenged = False
            for _player in state.players:
                if (
                    _player.team_num != player.team_num
                    and distance(_player.car_data.position, state.ball.position)
                    < self.min_distance
                ):
                    challenged = True
                    break
            if challenged:
                if stable:
                    if player.on_ground:
                        return reward - 0.5
                    else:
                        if player.has_flip:
                            # small reward for jumping
                            return reward + 2
                        else:
                            # print("PLAYER FLICKED!!!")
                            # big reward for flicking
                            return reward + 5
            else:
                if stable:
                    return reward + 1

        return reward
