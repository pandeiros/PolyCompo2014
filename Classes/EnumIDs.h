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
        PLAYER,
        FRONT
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

    static float playerSpeed = 40000.f;
    static float playerMissileSpeed = 100000.f;
    static float enemyMissileSpeed = 50000.f;
    static float enemySpeed = 20000.f;
    static float starSpeed = 10.f;
}

namespace Missiles{
    enum Type{
        M_WATERBALL,
        M_FIREBALL,
        M_ENEMYS_BALL
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
        HARD = 30,
        MEDIUM_CONDITION = 1000,
        HARD_CONDITION = 3000
    };

    static int shootingFrequency = 200;
}

namespace Cutscenes {
    enum Intro {
        _1_SPRITE_PISCES = 0,
        _2_LABEL_PISCES = 3,
        _3_LABEL_TEXT_1 = 5,
        _4_LABEL_TEXT_2 = 9,
        _5_LABEL_TEXT_3 = 13,
        _6_SHADER_INTRO = 17,
        _6a_SHADER_TEXT = 19,
        _7_DESTROYER_INTRO = 25,
        _7a_DESTROYER_TEXT = 27,
        _8_DEAF_STAR = 33,
        _9_LASER = 41,
        _9a_LASER_TEXT = 43,
        _10_FLASH = 46,
        _11_AQUARIUS = 51,
        _12_CONTINUE = 57,
    };

    enum Menu {
        _0_MENU_INIT = 0,
        _1_MOVE_TITLE = 2,
        _2_SHOW_GUI = 4,
        _3_BLINK_START_BUTTON = 5
    };

    static std::string intro1 = "Once upon a time, in a not far away galaxy,";
    static std::string intro2 = "there were Pisces, shining peacefully among the stars.";
    static std::string intro3 = "But their days were not meant to last forever...";
    static std::string intro4 = "Evil and meshed-up Dart Shader was planning to destroy";
    static std::string intro5 = "what was left of this magnificent pisce of star alignment.";
    static std::string intro6 = "Surrounded by his huge fleet of desTroyARRRs, Dart Shader";
    static std::string intro7 = "revealed the most powerful weapon in the entire universe...";
    static std::string intro8 = "Deaf Star.";
    static std::string intro9 = "            ...and torn Pisces into pieces.";
    static std::string intro10 = "But the crown jewel of the space was not left unavenged.";
    static std::string intro11 = "There was one last hope to end Dart Shader's madness...";
    static std::string intro12 = "Aquarius.";
    static std::string intro13 = "                                                                                           press Enter to continue...";
    
}

namespace Entities {
    enum Type {
        WATERBALL,
        FIREBALL,
        LASER,
        PLAYER,
        ENEMY,
    };

    static float rageDuration = 5.f;
    static int rageCharging = 15;
    static int maxHP = 100;
}

namespace Damage {
    enum Type {
        WATERBALL_DMG = 20,
        FIREBALL_DMG = 50,
        ENEMY_DMG = 30,
        ENEMY_PROJ_DMG = 5,
        FATAL = 1000
    };
}


#endif