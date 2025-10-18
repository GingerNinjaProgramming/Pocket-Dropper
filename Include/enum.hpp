#ifndef ENUM_HPP
#define ENUM_HPP

enum FrictionLevel{
    Normal = 0,
    Slippery = 9,
};

enum GameState {
    Playing,
    Paused
};

enum EnemyType {
    Platform,
    Chaser
};

enum PlayerState {
    Idle,
    Falling,
    Landed,
    Jumping,
    Moving_L,
    Moving_R
};
#endif