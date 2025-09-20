class ClearReward(RewardFunction):
def __init__(self, protected_distance=1200, punish_area_entry=False, non_participation_reward=0.0):
        self.protected_distance = protected_distance
        self.punish_area_entry=punish_area_entry
        self.non_participation_reward = non_participation_reward
        self.needs_clear = False
        self.goal_spot = np.array([0, -5120, 0])

    def reset(self, initial_state: GameState):
        self.needs_clear = False

    def get_reward(
            self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        ball_loc = state.ball.position
        if player.team_num != 0:
            ball_loc = state.inverted_ball.position

        coord_diff = self.goal_spot - ball_loc
        ball_dist_2d = np.linalg.norm(coord_diff[:2])
        #ball_dist_2d = math.sqrt(coord_diff[0]*coord_diff[0] + coord_diff[1]*coord_diff[1])
        reward = 0

        if self.needs_clear:
            if ball_dist_2d > self.protected_distance:
                self.needs_clear = False
                if state.last_touch == player.car_id:
                    reward += 1
                else:
                    reward += self.non_participation_reward
        else:
            if ball_dist_2d < self.protected_distance:
                self.needs_clear = True
                if self.punish_area_entry:
                    reward -= 1
        return reward
