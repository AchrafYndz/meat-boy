#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// The aspect ratio should be 9:16
// 480 p
const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 853;

// 720p
// const int WINDOW_WIDTH = 720;
// const int WINDOW_HEIGHT = 1280;

const float TIME_PER_FRAME = 1 / 60.0f;
const int TILE_SIZE = 256;
const float SCALE = (WINDOW_WIDTH / 15.0f) / TILE_SIZE;

#endif // GAME_CONSTANTS_H
