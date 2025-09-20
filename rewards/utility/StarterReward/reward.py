class StarterReward(RewardFunction):
def __init__(self):
        super().__init__()
        self.goal_reward = 10
        self.boost_weight = 0.1
        self.rew = CombinedReward(
            (
                EventReward(team_goal=self.goal_reward, concede=-self.goal_reward, demo=self.goal_reward/3),
                TouchVelChange(),
                VelocityBallToGoalReward(),
                VelocityPlayerToBallReward(),
                JumpTouchReward(min_height=120),
                KickoffReward(boost_punish=False)
            ),
            (1.0, 1.5, 0.075, 0.075, 2.0, 0.1))
            #(1.0, 1.0, 0.1, 2.0, 0.3334, 0.05))

    def reset(self, initial_state: GameState):
        self.rew.reset(initial_state)

    def get_reward(self, player: PlayerData, state: GameState, previous_action: np.ndarray) -> float:
        return self.rew.get_reward(player, state, previous_action)
