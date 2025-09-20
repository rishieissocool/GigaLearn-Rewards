class TweakedVelocityPlayerToGoalReward(RewardFunction):
def __init__(self, max_leeway=100, default_power=0.0) -> None:
        super().__init__()
        self.max_leeway = max_leeway
        self.default_power = default_power

    def reset(self, initial_state: GameState) -> None:
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        ball = state.ball
        player_pos = player.car_data.position
        player_goal = BLUE_GOAL_BACK
        if player.team_num == ORANGE_TEAM:
            ball = state.inverted_ball
            player_pos = player.inverted_car_data.position
            player_goal = ORANGE_GOAL_BACK

        diff = player_pos - ball.position
        if diff[1] < self.max_leeway:
            return 0

        direction = normalize(np.array(player_goal) - player_pos)
        vel = player.car_data.linear_velocity
        norm_pos_diff = direction / np.linalg.norm(direction)
        vel = vel/CAR_MAX_SPEED
        return float(np.dot(norm_pos_diff, vel))
