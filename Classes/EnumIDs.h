#ifndef _ENUM_IDS
#define _ENUM_IDS

namespace Layers {
    enum SceneLayers {
        BACKGROUND,
        SECOND_PLAN,
        GUI,
        ENTITIES,
        MISSILES,
        PICKUPS,
        PLAYER
    };
}

namespace States {
    enum PlayerStates {
        P_IDLE,
        P_MOVE
    };

    enum SceneStates {
        S_GAME,
        S_MENU,
        S_PAUSE,
        S_INTRO
    };
}

namespace Movement {
    enum Directions {
        UP = 1,
        RIGHT = 1 << 1,
        DOWN = 1 << 2,
        LEFT = 1 << 3,
        UR = 1 << 4,
        DR = 1 << 5,
        DL = 1 << 6,
        UL = 1 << 7
    };

    static float playerSpeed = 400.f;
    static float missileSpeed = 1000.f;
    static float enemySpeed = 200.f;
    static float starSpeed = 10.f;
}

namespace Missiles{
    enum Type{
        M_WATERBALL = 0,
        M_ENEMYS_BALL = 1
    };
}

namespace Enemies{
    enum Type{
        E_TIEFIGHTER = 0,
        E_OTHER_ = 1
    };

    enum Difficulty {
        EASY = 100,
        MEDIUM = 70,
        HARD = 30
    };
}

namespace Cutscenes {
    enum Intro {
        _1_SPRITE_PISCES = 0,
        _2_LABEL_PISCES = 3,
        _3_LABEL_TEXT_1 = 5,
        _4_LABEL_TEXT_2 = 9,
        _5_LABEL_TEXT_3 = 13,
        _6_SHADER_INTRO = 17,
        _7_DESTROYER_INTO = 22,
        _8_DEAF_STAR = 26
    };
    
}

#endif