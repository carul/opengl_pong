#ifndef DEFINES_HPP
#define DEFINES_HPP
#define DEBUG
#include <vector>
extern bool DOWN_PRESSED;
extern bool UP_PRESSED;
extern bool S_PRESSED;
extern bool W_PRESSED;
extern double DELTATIME;
extern bool GAME_PAUSED;
extern unsigned short scorep1;
extern unsigned short scorep2; 
extern std::vector<float> buttonTimers;

#define BORDER_WIDTH 0.96f

#define BORDER_DATA { \
  {{-1.0f, 1.0f}},\
  {{-1.0f, -1.0f}},\
  {{1.0f, -1.0f}},\
  {{1.0f, 1.0f}},\
  {{-BORDER_WIDTH, BORDER_WIDTH}},\
  {{-BORDER_WIDTH, -BORDER_WIDTH}},\
  {{BORDER_WIDTH, -BORDER_WIDTH}},\
  {{BORDER_WIDTH, BORDER_WIDTH}}\
}

#define BORDER_INDICES {\
  0, 5, 1,\
  0, 5, 4,\
  1, 6, 2,\
  1, 6, 5,\
  2, 7, 3,\
  2, 7, 6,\
  3, 4, 0,\
  3, 4, 7\
}


/*

  0  3


  1  2

*/
#define PADDLE1_DATA {\
  {{-0.85f, 0.1f, 1.0f, 1.0f, 1.0f, 1.0f}},\
  {{-0.85f, -0.1f}},\
  {{-0.82f, -0.1f, 1.0f, 1.0f, 0.0f, 1.0f}},\
  {{-0.82f, 0.1f}}\
}


/*

  3  0


  2  1

*/
#define PADDLE2_DATA {\
  {{0.85f, 0.1f, 1.0f, 0.0f, 0.0f, 1.0f}},\
  {{0.85f, -0.1f}},\
  {{0.82f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f}},\
  {{0.82f, 0.1f}}\
}

#define PADDLE1_INDICES {\
  0, 1, 2,\
  0, 2, 3\
}

#define PADDLE2_INDICES {\
  0, 1, 2,\
  0, 2, 3\
}

#define BALL_WIDTH 0.03f



/*
    5  4
  0      3
    1  2
*/
#define BALL_DATA {\
  {{-BALL_WIDTH, 0.0f}},\
  {{-BALL_WIDTH/2, -1.1*BALL_WIDTH}},\
  {{BALL_WIDTH/2, -1.1*BALL_WIDTH}},\
  {{BALL_WIDTH, 0.0f}},\
  {{BALL_WIDTH/2, BALL_WIDTH}},\
  {{-BALL_WIDTH/2, BALL_WIDTH}}\
}

#define BALL_INDICES {\
  0, 1, 5,\
  2, 3, 4,\
  1, 2, 4,\
  1, 4, 5\
}

#define PC_ICON_DATA {\
  {{-0.02f, 0.02f}},\
  {{-0.02f, -0.02f}},\
  {{0.02f, -0.02f}},\
  {{0.02f, 0.02f}},\
  {{-0.02f, -0.04f}},\
  {{0.02f, -0.04f}},\
  {{0.02f, -0.06f}},\
  {{-0.02f, -0.06f}},\
  {{0.028f, -0.02f}},\
  {{0.028f, -0.06f}},\
  {{0.04f, -0.06f}},\
  {{0.04f, -0.02f}}\
}

#define PC_ICON_INDICES {\
  0, 1, 2,\
  2, 3, 0,\
  4, 5, 6,\
  6, 7, 4,\
  8, 9, 10,\
  10, 11, 8\
}


#define PAUSE_ICON_DATA {\
  {{0.0f, 0.0f}},\
  {{0.0f, -0.084f}},\
  {{0.02f, 0.0f}},\
  {{0.02f, -0.084f}},\
  {{0.02f, -0.02f}},\
  {{0.04f, -0.02f}},\
  {{0.04f, 0.0f}},\
  {{0.06f, 0.0f}},\
  {{0.04f, -0.04f}},\
  {{0.06f, -0.04f}},\
  {{0.06f, -0.06f}},\
  {{0.02f, -0.04f}},\
  {{0.02f, -0.06f}}\
}

#define PAUSE_ICON_INDICES {\
  0, 1, 2,\
  1, 2, 3,\
  4, 5, 6,\
  2, 6, 4,\
  7, 8, 9,\
  6, 7, 8,\
  11, 12, 10,\
  10, 11, 9\
}

#define POINT_DATA {\
  {{0.0f, 0.0f}},\
  {{0.02f, 0.0f}},\
  {{0.02f, 0.04f}},\
  {{0.0f, 0.04f}}\
}

#define POINT_INDICES {\
  0, 1, 2,\
  2, 3, 0\
}


#endif
