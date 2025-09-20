class ThreeManRewards(RewardFunction):
def __init__(self, min_spacing: float = 1500):
        super().__init__()
        self.min_spacing = min_spacing
        self.vel_reward = VelocityBallToGoalReward()
        self.KOR = KickoffReward()

    def spacing_reward(self, player: PlayerData, state: GameState, role: int):
        reward = 0
        if role != 0:
            for p in state.players:
                if p.team_num == player.team_num and p.car_id != player.car_id:
                    separation = distance(player.car_data.position, p.car_data.position)
                    if separation < self.min_spacing:
                        reward -= 1 - (separation / self.min_spacing)
        return reward

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        player_distances = []
        for p in state.players:
            if p.team_num == player.team_num:
                player_distances.append(
                    (distance(p.car_data.position, state.ball.position), p.car_id)
                )

        role = 0
        player_distances.sort(key=lambda x: x[0])
        for count, pd in enumerate(player_distances):
            if pd[1] == player.car_id:
                role = count
                break

        reward = self.spacing_reward(player, state, role)
        if role == 1:
            reward += self.vel_reward.get_reward(player, state, previous_action)
            reward += self.KOR.get_reward(player, state, previous_action)

        return reward
