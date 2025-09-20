class TouchBallReward(RewardFunction):
def __init__(
        self,
        min_touch: float = 0.05,
        min_height: float = 170,
        min_distance: float = 300,
        aerial_weight: float = 0.15,
        air_reward: bool = True,
        first_touch: bool = False,
    ):
        self.min_touch = min_touch
        self.min_height = min_height
        self.aerial_weight = aerial_weight
        self.air_reward = air_reward
        self.first_touch = first_touch
        self.min_distance = min_distance

    def reset(self, initial_state: GameState):
        pass

    def get_closest_enemy_distance(self, player: PlayerData, state: GameState) -> float:
        closest_dist = 50000
        for car in state.players:
            if car.team_num != player.team_num:
                dist = distance2D(player.car_data.position, car.car_data.position)
                if dist < closest_dist:
                    closest_dist = dist
        return closest_dist

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        if player.ball_touched:
            if (
                self.first_touch
                and state.ball.position[0] == 0
                and state.ball.position[1] == 0
            ):
                reward += 5
            if state.ball.position[2] >= self.min_height:

                if (
                    self.min_distance == 0
                    or self.get_closest_enemy_distance(player, state)
                    > self.min_distance
                ):
                    reward += max(
                        [
                            self.min_touch,
                            (
                                abs(state.ball.position[2] - BALL_RADIUS)
                                ** self.aerial_weight
                            )
                            - 1,
                        ]
                    )
            if self.air_reward and not player.on_ground:
                if not player.has_flip:
                    reward += 1
                else:
                    reward += 0.5

        return reward
