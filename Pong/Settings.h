#pragma once


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Refresh rates
const int PLAYER_TAB_REFRESH_VALUE = 5;
const int PLAYER_TAB_ANIMATION_REFRESH_VALUE = 100;

// Score position
const int SCORE_Y = SCREEN_HEIGHT  - 100;
const int SCORE_ONE_X = (SCREEN_WIDTH / 2) - 100;
const int SCORE_TWO_X = (SCREEN_WIDTH / 2) + 50;

// Tab distance
const int TAB_DISTANCE = 45;
const int TAB_SPEED = 5;

const int PLAYER_ONE_POSITION_X = TAB_DISTANCE;
const int PLAYER_TWO_POSITION_X = SCREEN_WIDTH - TAB_DISTANCE;

// Gameplay constants
const int SCORE_FOR_VICTORY = 10;
const int POWERUP_FREQUENCY = 501;
const int POWERUP_DURATION = 5000;
const int DEFAULT_BALL_SPEED = 4;
const int HIGH_BALL_SPEED = 8;

// Extern variables
extern int tabWidth;
extern int tabHeight;
