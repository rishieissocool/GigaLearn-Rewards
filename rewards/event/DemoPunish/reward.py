import math
from rlgym.utils.reward_functions import RewardFunction
from rlgym.utils.gamestates import GameState, PlayerData
from rlgym.utils import math as rl_math
from bubo_misc_utils import *  # sign, normalize, distance, distance2D, clamp
import numpy as np

SIDE_WALL_X = 4096  # +/-  
BACK_WALL_Y = 5120  # +/-
CEILING_Z = 2044
BACK_NET_Y = 6000  # +/-

GOAL_HEIGHT = 642.775

ORANGE_GOAL_CENTER = (0, BACK_WALL_Y, GOAL_HEIGHT / 2)
BLUE_GOAL_CENTER = (0, -BACK_WALL_Y, GOAL_HEIGHT / 2)

# Often more useful than center
ORANGE_GOAL_BACK = (0, BACK_NET_Y, GOAL_HEIGHT / 2)
BLUE_GOAL_BACK = (0, -BACK_NET_Y, GOAL_HEIGHT / 2)

BALL_RADIUS = 92.75

BALL_MAX_SPEED = 6000
CAR_MAX_SPEED = 2300
SUPERSONIC_THRESHOLD = 2200
CAR_MAX_ANG_VEL = 5.5

BLUE_TEAM = 0
ORANGE_TEAM = 1
NUM_ACTIONS = 8


class DemoPunish(RewardFunction):
    def __init__(self) -> None:
        super().__init__()
        self.demo_statuses = [True for _ in range(64)]

    def reset(self, initial_state: GameState) -> None:
        self.demo_statuses = [True for _ in range(64)]

    def get_reward(self, player: PlayerData, state: GameState, previous_action: np.ndarray) -> float:
        reward = 0
        if player.is_demoed and not self.demo_statuses[player.car_id]:
            reward = -1

        self.demo_statuses[player.car_id] = player.is_demoed
        return reward