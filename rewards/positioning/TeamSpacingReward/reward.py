class TeamSpacingReward(RewardFunction):
def __init__(self, min_spacing: float = 1000) -> None:
        super().__init__()
        self.min_spacing = clamp(math.inf, 0.0000001, min_spacing)

    def reset(self, initial_state: GameState):
        pass

    def spacing_reward(self, player: PlayerData, state: GameState) -> float:
        reward = 0
        for p in state.players:
            if p.team_num == player.team_num and p.car_id != player.car_id and not player.is_demoed and not p.is_demoed:
                separation = distance(player.car_data.position, p.car_data.position)
                if separation < self.min_spacing:
                    reward -= 1-(separation / self.min_spacing)

        return reward

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        return self.spacing_reward(player, state)
