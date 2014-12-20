#ifndef _ENUM_IDS
#define _ENUM_IDS

namespace Layers {
    enum SceneLayers {
        BACKGROUND,
        SECOND_PLAN,
        GUI,
        ENTITIES
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
		NE = 1 << 4,
		NW = 1 << 5,
		SE = 1 << 6,
		SW = 1 << 7
    };

    static float playerSpeed = 10.f;
}

namespace Missiles{
	enum Type{
		M_WATERBALL = 0,
		M_ENEMYS_BALL = 1
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