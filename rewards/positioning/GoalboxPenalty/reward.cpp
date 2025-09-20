#pragma once
#include "Reward.h"
#include "../Math.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace RLGC {

    // Constants from rewards.py
    constexpr float SIDE_WALL_X = 4096.0f;
    constexpr float BACK_WALL_Y = 5120.0f;
    constexpr float CEILING_Z = 2044.0f;
    constexpr float BACK_NET_Y = 6000.0f;
    constexpr float GOAL_HEIGHT = 642.775f;
    const Vec ORANGE_GOAL_CENTER = {0.0f, BACK_WALL_Y, GOAL_HEIGHT / 2.0f};
    const Vec BLUE_GOAL_CENTER = {0.0f, -BACK_WALL_Y, GOAL_HEIGHT / 2.0f};
    const Vec ORANGE_GOAL_BACK = {0.0f, BACK_NET_Y, GOAL_HEIGHT / 2.0f};
    const Vec BLUE_GOAL_BACK = {0.0f, -BACK_NET_Y, GOAL_HEIGHT / 2.0f};
    constexpr float BALL_RADIUS = 92.75f;
    constexpr float BALL_MAX_SPEED = 6000.0f;
    constexpr float CAR_MAX_SPEED = 2300.0f;
    constexpr float SUPERSONIC_THRESHOLD = 2200.0f;
    constexpr float CAR_MAX_ANG_VEL = 5.5f;
    constexpr int BLUE_TEAM = 0;
    constexpr int ORANGE_TEAM = 1;
    class GoalboxPenalty : public Reward {
    public:
        virtual float GetReward(const Player& player, const GameState& state, bool isFinal) override {
            // TODO: Implement reward logic
            return 0.0f;
        }
    };
}
