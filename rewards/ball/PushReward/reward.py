class PushReward(RewardFunction):
def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        pos = state.ball.position
        if player.team_num != BLUE_TEAM:
            pos = state.inverted_ball.position

        if pos[1] > 0:
            y_scale = pos[1] / 5213
            if abs(pos[0]) > 800:
                x_scale = (abs(pos[0]) / 4096) * y_scale
                scale = y_scale - x_scale
                return scale
            return y_scale

        elif pos[1] < 0:
            y_scale = pos[1] / 5213
            if abs(pos[0]) > 800:
                x_scale = (abs(pos[0]) / 4096) * abs(y_scale)
                scale = y_scale + x_scale
                return scale
            return y_scale

        return 0
