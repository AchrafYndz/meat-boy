#ifndef GAME_FLOATVECTOR2_H
#define GAME_FLOATVECTOR2_H

struct floatVector2 {
    float x;
    float y;

    floatVector2() {
        x = 0;
        y = 0;
    }

    floatVector2(float x_, float y_) {
        x = x_;
        y = y_;
    }
};

#endif // GAME_FLOATVECTOR2_H
