class ChallengeReward(RewardFunction):
def __init__(self, challenge_distance=300):
        super().__init__()
        self.challenge_distance = challenge_distance

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        if (
            not player.on_ground
            and distance(player.car_data.position, state.ball.position)
            < self.challenge_distance
        ):
            for _player in state.players:
                if (
                    _player.team_num != player.team_num
                    and distance(_player.car_data.position, state.ball.position)
                    < self.challenge_distance
                ):
                    reward += 0.1
                    if not player.has_flip:
                        # ball_dir_norm = normalize(state.ball.position-player.car_data.position)
                        # direction = ball_dir_norm.dot(normalize(player.car_data.linear_velocity))
                        # return direction + reward
                        reward += 0.9
                    break

        return reward
