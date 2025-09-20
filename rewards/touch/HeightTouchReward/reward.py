class HeightTouchReward(RewardFunction):
def __init__(self, min_height=92, exp=0.2, coop_dist=0):
        super().__init__()
        self.min_height = min_height
        self.exp = exp
        self.cooperation_dist = coop_dist

    def reset(self, initial_state: GameState):
        pass

    def cooperation_detector(self, player: PlayerData, state: GameState):
        for p in state.players:
            if p.car_id != player.car_id and \
                    distance(player.car_data.position, p.car_data.position) < self.cooperation_dist:
                return True

        return False


    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        if player.ball_touched:
            if state.ball.position[2] >= self.min_height:
                if not player.on_ground or self.cooperation_dist < 90 or not self.cooperation_detector(player, state):
                    if player.on_ground:
                        reward += clamp(5000, 0.0001, (state.ball.position[2]-92)) ** self.exp
                    else:
                        reward += clamp(500, 1, (state.ball.position[2] ** (self.exp*2)))

            elif not player.on_ground:
                reward += 1

        return reward
