class VelocityBallToGoalReward(RewardFunction):
    def __init__(self):
        super().__init__()

    def reset(self, initial_state: GameState):
        pass

    def get_reward(self, player: PlayerData, state: GameState, previous_action: np.ndarray) -> float:
        ball_pos = state.ball.position
        goal_pos = np.array([0, 6000, 321.3875]) if player.team_num == 0 else np.array([0, -6000, 321.3875])
        pos_diff = ball_pos - goal_pos
        norm_pos_diff = pos_diff / np.linalg.norm(pos_diff)
        vel = state.ball.linear_velocity / 6000
        return np.dot(norm_pos_diff, vel)