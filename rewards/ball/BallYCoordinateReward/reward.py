class BallYCoordinateReward(RewardFunction):
def __init__(self, exponent=1):
        # Exponent should be odd so that negative y -> negative reward
        self.exponent = exponent

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        if player.team_num == BLUE_TEAM:
            return (
                state.ball.position[1] / (BACK_WALL_Y + BALL_RADIUS)
            ) ** self.exponent
        else:
            return (
                state.inverted_ball.position[1] / (BACK_WALL_Y + BALL_RADIUS)
            ) ** self.exponent
