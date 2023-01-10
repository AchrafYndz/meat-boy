#ifndef GAME_VEC2_H
#define GAME_VEC2_H

struct Vec2 {
    float x;
    float y;

    Vec2() {
        x = 0;
        y = 0;
    }

    Vec2(float _x, float _y) {
        x = _x;
        y = _y;
    }
};

#endif // GAME_VEC2_H
