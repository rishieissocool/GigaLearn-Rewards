class AirReward(RewardFunction):
def __init__(
        self,
    ):
        super().__init__()

    def reset(self, initial_state: GameState):
        pass

    def get_reward(
        self, player: PlayerData, state: GameState, previous_action: np.ndarray
    ) -> float:
        if not player.on_ground:
            if player.has_flip:
                return 0.5
            else:
                return 1
        return 0


if __name__ == "__main__":
    pass
