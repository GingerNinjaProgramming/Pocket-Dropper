#ifndef ENUM_HPP
#define ENUM_HPP

enum FrictionLevel{
    Normal = 0,
    Slippery = 9,
};

enum GameState {
    MainMenu,
    Quit,
    Playing,
    Paused,
    Options
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

enum SoundType {
    PlayerHit,
    EnemyHit,
    PlayerJump,
    PlayerLand,
    PlayerShoot,
    EnemyDeath
};

enum UIType {
    Button,
    Checkbox
};

#endif