class ModifiedTouchReward(RewardFunction):
def __init__(self, min_change: float = 300, min_height: float = 200, vel_scale: float = 1, touch_scale: float = 1, jump_reward: bool = False, jump_scale: float = 0.1, tick_min: int = 0):
        super().__init__()
        self.psr = PowerShotReward(min_change)
        self.min_height = min_height
        self.height_cap = 2044-92.75
        self.vel_scale = vel_scale
        self.touch_scale = touch_scale
        self.jump_reward = jump_reward
        self.jump_scale = jump_scale
        self.tick_count = 0
        self.tick_min = tick_min

    def reset(self, initial_state: GameState):
        self.psr.reset(initial_state)
        self.tick_count = 0

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        psr = self.psr.get_reward(player, state, previous_action)
        if player.ball_touched:
            if self.tick_count <= 0:
                self.tick_count = self.tick_min
                reward += abs(psr * self.vel_scale)

                if not player.on_ground:
                    if self.jump_reward:
                        reward += self.jump_scale
                        if not player.has_flip:
                            reward += self.jump_scale
                    if state.ball.position[2] > self.min_height:
                        reward += abs((state.ball.position[2]/self.height_cap) * self.touch_scale)
            else:
                self.tick_count -= 1
        else:
            self.tick_count -= 1

        return reward
