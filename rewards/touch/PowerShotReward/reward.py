class PowerShotReward(RewardFunction):
def __init__(self, min_change: float = 300):
        super().__init__()
        self.min_change = min_change
        self.last_velocity = np.array([0, 0])

    def reset(self, initial_state: GameState):
        self.last_velocity = np.array([0, 0])

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        cur_vel = np.array(
            [state.ball.linear_velocity[0], state.ball.linear_velocity[1]]
        )
        if player.ball_touched:
            vel_change = rl_math.vecmag(self.last_velocity - cur_vel)
            if vel_change > self.min_change:
                reward = vel_change / (2300*2)

        self.last_velocity = cur_vel
        return reward
