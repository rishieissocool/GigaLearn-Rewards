class MillennialKickoffReward(RewardFunction):
def __init__(self):
        super().__init__()

    def reset(self, initial_state: GameState):
        pass

    def closest_to_ball(self, player: PlayerData, state: GameState) -> bool:
        player_dist = np.linalg.norm(player.car_data.position - state.ball.position)
        for p in state.players:
            if p.team_num == player.team_num and p.car_id != p.car_id:
                dist = np.linalg.norm(p.car_data.position - state.ball.position)
                if dist < player_dist:
                    return False

        return True

    def get_reward(self, player: PlayerData, state: GameState, previous_action: np.ndarray) -> float:
        if state.ball.position[0] == 0 and state.ball.position[1] == 0 and self.closest_to_ball(player, state):
            return -1
        return 0
