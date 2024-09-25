#include <paddle.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

int main() {
    pong::init();
    std::string input;
    while (pong::running)
    {
        pong::nextFrame(std::cout);

        std::cin >> input;
        pong::process(input);
        pong::tick();
    }
    if(pong::winner == pong::PLAYER_WINNER) {
        std::cout << "YOU WIN!" << std::endl;
    } else if (pong::winner == pong::BOT_WINNER) {
        std::cout << "YOU LOSE" << std::endl;
    }
}


int pong::playerY;
int pong::botY;
bool pong::running;
int pong::winner;
int pong::ballX;
int pong::ballY;
int pong::ballYDirection;
int pong::ballXDirection;
std::string pong::topAndBottom;

void pong::init() {
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    playerY = 1;
    botY = 1;
    ballY = 2;
    ballX = WIDTH/2;
    ballXDirection = -1;
    ballYDirection = 0;
    winner = 0;
    running = true;
    topAndBottom = "+";
    for (int i = 0; i < WIDTH; i++)
    {
        topAndBottom+="-";
    }
    topAndBottom += "+";
}

void pong::writeLine(std::ostream& output, std::string str){
    output << str << std::endl;
}

bool pong::isInBounds(int x1, int y1, int len, int x2, int y2) {
    if(x2 != x1)
        return false;
    
    if(y2 < y1 || y2 > y1 + (len-1))
        return false;

    return true;
}

bool pong::isInBotBounds(int x, int y) {
    return isInBounds(BOT_X, botY, PADDLE_LEN, x, y);
}

bool pong::isInPlayerBounds(int x, int y) {
    return isInBounds(PLAY_X, playerY, PADDLE_LEN, x, y);
}

void pong::nextFrame(std::ostream& output) {
    output << topAndBottom << std::endl;
    for (size_t y = 0; y < HEIGHT; y++)
    {
        output << "|";
        for (size_t x = 0; x < WIDTH; x++)
        {
            char outputCharacter = ' ';
            if(pong::isInPlayerBounds(x,y) || pong::isInBotBounds(x,y)) {
                outputCharacter = '#';
            } else if (x == ballX && y == ballY) {
                outputCharacter = '@';
            }
            output << outputCharacter;
        }
        output << "|" << std::endl;
    }
    output << topAndBottom << std::endl;
    
}

void pong::tick() {
    if(ballY > botY+1) {
        botY += 1;
    } else if (ballY < botY+1) {
        botY -= 1;
    }

    if(botY+PADDLE_LEN-1 >= HEIGHT) {
            botY = HEIGHT - PADDLE_LEN;
    }

    if(botY <= 0) {
        botY = 0;
    }

    ballX += ballXDirection;
    ballY += ballYDirection;

    if(pong::isInPlayerBounds(ballX,ballY) || pong::isInBotBounds(ballX,ballY)) {
        if(ballX == PLAY_X) {

            //1 top//3 bottom
            //if 1 => -1
            //if 3 => 1
            //3-2 == 1, 1-2==-1
            //std::cout << "PLAY" << std::endl;
            ballYDirection = (ballY - playerY+1)-2;
            //std::cout << ballYDirection << std::endl;
        } else {
           //std::cout << "BOT" << std::endl;
            ballYDirection = (ballY - botY+1)-2;
            //std::cout << ballYDirection << std::endl;
        }
        ballXDirection = -ballXDirection;
        ballX += ballXDirection;
        ballY += ballYDirection;

    }
    
    if(ballY < 0 || ballY == HEIGHT) {
        ballYDirection *= -1;
        ballY += ballYDirection;
    }

    if(ballX <= 0) {
        running = false;
        winner = BOT_WINNER;
    } else if (ballX >= WIDTH) {
        running = false;
        winner = PLAYER_WINNER;
    }



}

void pong::process(std::string input) {
    if(input == "d" || input == "down") {
        playerY += 1;
        if(playerY+PADDLE_LEN-1 >= HEIGHT) {
            playerY = HEIGHT - PADDLE_LEN;
        }
    } else if (input == "u" || input == "up") {
        playerY -= 1;
        if(playerY <= 0) {
            playerY = 0;
        }
    }
}