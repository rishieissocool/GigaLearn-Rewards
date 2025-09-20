class PositioningReward(RewardFunction):
def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        ball = state.ball.position
        pos = player.car_data.position
        if player.team_num != BLUE_TEAM:
            ball = state.inverted_ball.position
            pos = player.inverted_car_data.position

        reward = 0.0
        if ball[1] < pos[1]:
            diff = ball[1] - pos[1]
            reward = -clamp(1, 0, abs(diff) / 5000)
        return reward
