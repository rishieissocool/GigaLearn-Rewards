class CenterReward(RewardFunction):
def __init__(self, centered_distance=1200, punish_area_exit=False, non_participation_reward=0.0):
        self.centered_distance = centered_distance
        self.punish_area_exit = punish_area_exit
        self.non_participation_reward = non_participation_reward
        self.centered = False
        self.goal_spot = np.array([0, 5120, 0])

    def reset(self, initial_state: GameState):
        self.centered = False

    def get_reward(
            self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        ball_loc = state.ball.position
        if player.team_num != 0:
            ball_loc = state.inverted_ball.position

        coord_diff = self.goal_spot - ball_loc
        ball_dist_2d = np.linalg.norm(coord_diff[:2])
        #ball_dist_2d = math.sqrt(coord_diff[0] * coord_diff[0] + coord_diff[1] * coord_diff[1])
        reward = 0

        if self.centered:
            if ball_dist_2d > self.centered_distance:
                self.centered = False
                if self.punish_area_exit:
                    reward -= 1
        else:
            if ball_dist_2d < self.centered_distance:
                self.centered = True
                if state.last_touch == player.car_id:
                    reward += 1
                else:
                    reward += self.non_participation_reward
        return reward
