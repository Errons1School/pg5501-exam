#ifndef SNAKEBACKEND_SNAKEIO_H
#define SNAKEBACKEND_SNAKEIO_H

#include "../modules/MTftScreen.h"
#include "../modules/MGyroscope.h"
#include "SnakeEnumAndStructs.h"

class SnakeIO {
public:

    SnakeIO(MGyroscope *pMGyroscope, MTftScreen *pMTftScreen);

    /* Gets input from user and maps it to digit that game understands
     * RETURN       int between 0 - 4*/
    int input();

    /* Prints board on standard output */
    void printBoard(Snake *pSnake, Food *pFood);

private:

    MTftScreen *pMTftScreen = nullptr;
    MGyroscope *pMGyroscope = nullptr;
};


#endif //SNAKEBACKEND_SNAKEIO_H
