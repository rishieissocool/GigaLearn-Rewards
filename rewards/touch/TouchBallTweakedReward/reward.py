class TouchBallTweakedReward(RewardFunction):
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
        self.min_change = 500
        self.last_velocity = np.array([0, 0, 0])

    def reset(self, initial_state: GameState):
        self.last_velocity = np.array([0, 0, 0])

    def get_closest_enemy_distance(self, player: PlayerData, state: GameState) -> float:
        closest_dist = 50000
        for car in state.players:
            if car.team_num != player.team_num:
                dist = distance2D(state.ball.position, car.car_data.position)
                if dist < closest_dist:
                    closest_dist = dist
        return closest_dist

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        current_vel = state.ball.linear_velocity
        if player.ball_touched:
            if state.ball.position[2] >= self.min_height or (
                state.ball.position[2] >= BALL_RADIUS + 20
                and (
                    self.min_distance == 0
                    or self.get_closest_enemy_distance(player, state)
                    > self.min_distance
                )
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
                reward += np.linalg.norm(self.last_velocity - current_vel) / 2300

            if self.air_reward and not player.on_ground:
                reward += 0.5
                if not player.has_flip:
                    reward += 0.5

        self.last_velocity = current_vel
        # if abs(state.ball.position[0]) > 3896 or abs(state.ball.position[1]) > 4920:
        #     reward *= 0.75
        return reward
