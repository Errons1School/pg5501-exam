#include "SnakeIO.h"

SnakeIO::SnakeIO(MGyroscope *pMGyroscope, MTftScreen *pMTftScreen) {
    this->pMGyroscope = pMGyroscope;
    this->pMTftScreen = pMTftScreen;
}

int SnakeIO::input() {
    unsigned long ulMillisOld = millis();
    unsigned long ulMillisNow = millis();
    static int iDirection = 0;
    int iInput = 0;
    int iTmp = 0;

    while ((ulMillisNow - ulMillisOld) < 1000) {
        iTmp = pMGyroscope->getLeftOrRight();

        if (iTmp != 0) {
            iInput = iTmp;
        }

        ulMillisNow = millis();
    }

    iDirection += iInput;
    if (iDirection < 0) {
        iDirection = 3;

    } else if (iDirection > 3) {
        iDirection = 0;
    }

    return iDirection;
}

void SnakeIO::printBoard(Snake *pSnake, Food *pFood) {
    // 0 == empty, 1 == snake, 2 == food
    int iGridSize = 135;
    int iGamePixel = 15;
    int iWhatToPrint = 0; // grass
    int iWhatDirection = 0;


    for (int y = 0; (y * iGamePixel) < iGridSize; ++y) {
        for (int x = 0; (x * iGamePixel) < iGridSize; ++x) {

//            Print snake body
            for (int i = 0; i < pSnake->iSnakeSize; ++i) {
                if (pSnake->paSnakeBody[i].iX == x && pSnake->paSnakeBody[i].iY == y) {
                    if (i == 0) {
                        iWhatToPrint = 1; // head
                    } else if (i == pSnake->iSnakeSize - 1) {
                        iWhatToPrint = 3; // tail
                    } else {
                        iWhatToPrint = 2; // body
                    }

                    iWhatDirection = pSnake->paSnakeBody[i].iDirection;
                    break;
                }
            }

//            Print food
            if (pFood->iX == x && pFood->iY == y) {
                iWhatToPrint = 4; // food
            }

            pMTftScreen->printTexture(iWhatToPrint, (x * iGamePixel), (y * iGamePixel), iWhatDirection);
            iWhatToPrint = 0;
            iWhatDirection = 0;
        }
    }
}