#pragma once

#include <iostream>
#include <sstream>
#include <ostream>

namespace pong
{
    extern int playerY;
    extern int botY;
    extern int ballX;
    extern int ballY;
    extern bool running;

    extern int ballXDirection;
    extern int ballYDirection;

    extern int winner;

    const int PLAYER_WINNER = 1;
    const int BOT_WINNER = 2;

    const int PLAY_X = 1;
    const int WIDTH = 31;
    const int BOT_X = WIDTH-2;
    const int HEIGHT = 9;
    const int PADDLE_LEN = 3;

    extern std::string topAndBottom;

    void init();
    void writeLine(std::ostream& output, std::string str);
    void nextFrame(std::ostream& output);

    bool isInBounds(int x1, int y1, int len, int x2, int y2);

    bool isInBotBounds(int x, int y);

    bool isInPlayerBounds(int x, int y);

    void tick();
    void process(std::string input);
}