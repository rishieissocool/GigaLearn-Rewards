# Gigalearn Rewards Collection

A comprehensive collection of reward functions for Gigalearn, organized by category and available in both C++ and Python implementations.

## Overview

This repository contains 56 carefully organized reward functions designed for training Rocket League agents with Gigalearn. Each reward is available in both C++ and Python formats, allowing for flexible integration into your training pipeline.

## Reward Categories

### 🎯 Event-Based Rewards (`rewards/event/`)
Rewards that respond to specific game events and state changes.

- **EventReward** - Comprehensive event tracking (goals, touches, shots, saves, demos, boost pickups)
- **DemoPunish** - Punishment for being demolished
- **BoostAcquisitions** - Rewards for collecting boost

### ⚡ Velocity Rewards (`rewards/velocity/`)
Rewards focused on player movement and speed optimization.

- **VelocityPlayerToBallReward** - Encourages movement toward the ball
- **SpeedReward** - Rewards forward speed with direction awareness
- **ForwardBiasReward** - Promotes forward-facing movement
- **FlatSpeedReward** - Horizontal speed optimization
- **NaiveSpeedReward** - Simple speed-based reward
- **SelectiveChaseReward** - Conditional ball chasing behavior
- **TweakedVelocityPlayerToGoalReward** - Goal-oriented movement with tweaks
- **RetreatReward** - Defensive retreat behavior

### 🎮 Touch Rewards (`rewards/touch/`)
Rewards for ball interaction and contact mechanics.

- **ClearReward** - Rewards defensive clears
- **HeightTouchReward** - Encourages high ball touches
- **JumpTouchReward** - Rewards aerial ball contact
- **ModifiedTouchReward** - Enhanced touch detection
- **PowerShotReward** - Rewards powerful shots
- **TouchBallReward** - Basic ball touching reward
- **TouchBallTweakedReward** - Refined touch mechanics

### 🚁 Aerial Rewards (`rewards/aerial/`)
Specialized rewards for aerial maneuvers and flight control.

- **AerialNavigation** - Aerial positioning and control
- **AerialTraining** - General aerial skill development
- **AirReward** - Basic aerial behavior
- **ChallengeReward** - Aerial challenges and contests
- **LandingRecoveryReward** - Safe landing mechanics

### ⚽ Ball Rewards (`rewards/ball/`)
Rewards focused on ball control, positioning, and goal-oriented behavior.

- **BallYCoordinateReward** - Ball positioning along Y-axis
- **CradleFlickReward** - Ball carrying and flicking mechanics
- **CradleReward** - Ball carrying behavior
- **DefenseTrainer** - Defensive ball handling
- **kickoff** - Kickoff-specific behavior
- **PositiveBallVelToGoalReward** - Goal-directed ball velocity
- **PushReward** - Ball pushing mechanics
- **VelocityBallDefense** - Defensive ball velocity control
- **velocityballtogoal** - Ball velocity toward goal
- **VersatileBallVelocityReward** - Flexible ball velocity rewards

### 📍 Positioning Rewards (`rewards/positioning/`)
Rewards for strategic positioning and spatial awareness.

- **CenterReward** - Field center positioning
- **DefenderReward** - Defensive positioning
- **DistanceReward** - Distance-based positioning
- **GoalboxPenalty** - Penalty for staying in goal box
- **GroundedReward** - Ground-based positioning
- **PlayerAlignment** - Team alignment rewards
- **PositioningReward** - General positioning mechanics
- **TeamSpacingReward** - Team spacing optimization
- **ThreeManRewards** - Three-player coordination

### 🎛️ Control Rewards (`rewards/control/`)
Rewards for car control, boost management, and mechanical skills.

- **BoostDiscipline** - Boost usage optimization
- **BoostTrainer** - Boost management training
- **ControllerModerator** - Input control moderation
- **FlipCorrecter** - Flip timing and correction
- **lavafloor** - Ground-level penalty system
- **MillennialKickoffReward** - Advanced kickoff mechanics
- **OmniBoostDiscipline** - Omnidirectional boost control
- **RuleOnePunishment** - Rule enforcement penalties
- **SaveBoostReward** - Boost conservation rewards

### 🔧 Utility Rewards (`rewards/utility/`)
Helper rewards and wrappers for advanced reward composition.

- **OncePerStepRewardWrapper** - Step-based reward limiting
- **PositivePlayerVelToBallReward** - Positive velocity toward ball
- **PositiveWrapperReward** - Positive reward enforcement
- **SequentialRewards** - Sequential reward composition
- **StarterReward** - Basic starting rewards

## Implementation in Gigalearn

### C++ Integration

To use these rewards in Gigalearn, add the desired reward class to your `commonrewards.h` file:

```cpp
#include "rewards/event/EventReward/reward.cpp"
#include "rewards/velocity/SpeedReward/reward.cpp"
#include "rewards/touch/TouchBallReward/reward.cpp"
// Add more rewards as needed
```

### Python Integration

For Python-based training, import the reward classes directly:

```python
from rewards.event.EventReward.reward import EventReward
from rewards.velocity.SpeedReward.reward import SpeedReward
from rewards.touch.TouchBallReward.reward import TouchBallReward
# Add more rewards as needed
```

### Combining Rewards

Both C++ and Python versions support reward combination:

**C++ Example:**
```cpp
// Create combined reward system
auto eventReward = std::make_unique<EventReward>(1.0f, 0.5f, -1.0f, 0.1f);
auto speedReward = std::make_unique<SpeedReward>();
auto touchReward = std::make_unique<TouchBallReward>(0.2f);
```

**Python Example:**
```python
from rlgym.utils.reward_functions import CombinedReward

combined_reward = CombinedReward([
    EventReward(goal=1.0, team_goal=0.5, concede=-1.0, touch=0.1),
    SpeedReward(),
    TouchBallReward(0.2)
])
```

## Reward Architecture

### C++ Structure
Each C++ reward inherits from the base `Reward` class and implements:
- `GetReward(const Player& player, const GameState& state, bool isFinal)` - Main reward calculation
- `Reset(const GameState& initialState)` - State reset functionality

### Python Structure
Each Python reward inherits from `RewardFunction` and implements:
- `get_reward(player, state, previous_action)` - Main reward calculation
- `reset(initial_state)` - State reset functionality

## File Organization

```
rewards/
├── event/          # Event-based rewards
├── velocity/       # Movement and speed rewards
├── touch/          # Ball interaction rewards
├── aerial/         # Aerial maneuver rewards
├── ball/           # Ball control and positioning
├── positioning/    # Strategic positioning
├── control/        # Car control and mechanics
└── utility/        # Helper and wrapper rewards
```

Each reward directory contains:
- `reward.cpp` - C++ implementation
- `reward.py` - Python implementation

## Usage Recommendations

### For Beginners
Start with these essential rewards:
1. **SpeedReward** - Basic movement training
2. **TouchBallReward** - Ball interaction
3. **EventReward** - Game event awareness

### For Intermediate Training
Add complexity with:
1. **VelocityPlayerToBallReward** - Ball chasing
2. **PositioningReward** - Strategic positioning
3. **BoostDiscipline** - Resource management

### For Advanced Training
Include specialized rewards:
1. **AerialNavigation** - Aerial mechanics
2. **ThreeManRewards** - Team coordination
3. **SequentialRewards** - Complex behavior chains

## Customization

All rewards are designed to be easily customizable through constructor parameters. Modify reward weights, thresholds, and behaviors by adjusting the initialization parameters to suit your specific training needs.

## Contributing

This reward collection is designed to be modular and extensible. Each reward is self-contained and can be used independently or combined with others to create complex training scenarios.

---

*This collection provides a solid foundation for training Rocket League agents with Gigalearn, covering all major aspects of gameplay from basic movement to advanced aerial mechanics.*
