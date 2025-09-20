class DefenderReward(RewardFunction):
def __init__(self):
        super().__init__()
        self.enemy_goals = 0


    def reset(self, initial_state: GameState):
        pass

    def get_reward(
            self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        reward = 0
        if player.team_num == BLUE_TEAM:
            e_score = state.orange_score
            defend_loc = BLUE_GOAL_CENTER
        else:
            e_score = state.blue_score
            defend_loc = ORANGE_GOAL_CENTER

        if e_score > self.enemy_goals:
            self.enemy_goals = e_score
            dist = distance2D(np.asarray(defend_loc), player.car_data.position)
            if dist > 900:
                reward -= clamp(1, 0, dist/10000)
        return reward
