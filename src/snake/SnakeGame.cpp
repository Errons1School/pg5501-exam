#include "SnakeGame.h"
#include "SnakeIO.h"

#include <Arduino.h>

SnakeGame::SnakeGame(MGyroscope *pMGyroscope, MTftScreen *pMTftScreen, MEeprom *pMEprom) {
    this->pMTftScreen = pMTftScreen;
    this->pMEprom = pMEprom;

    pSnakeIO = new SnakeIO(pMGyroscope, pMTftScreen);

    pSnake = (Snake *) calloc(1, sizeof(Snake));
    pSnake->iSnakeSize = 0;
    pSnake->iSnakeMaxSize = GRIDSIZE * GRIDSIZE;
    pSnake->paSnakeBody = (SnakeBody *) calloc(pSnake->iSnakeMaxSize, sizeof(SnakeBody));

    pFood = (Food *) calloc(1, sizeof(Food));
    iScore = 0;
}

void SnakeGame::startGame() {
    bool bIsAlive = true;
    int iDirection = 0;

    spawnSnake();

    while (bIsAlive) {
        spawnFood();
        pSnakeIO->printBoard(pSnake, pFood);
        iDirection = pSnakeIO->input();
        moveSnake(iDirection);
        bIsAlive = checkCollision();
    }

    printAndSaveScore();
}

void SnakeGame::moveSnake(int iDirection) {
    bool bSkipLast = false;
    int iNextBodyDirection = 0;

    for (int i = 0; i < pSnake->iSnakeSize; ++i) {

//        Makes the input for moving head towards neck impossible
        if (i == 0) {
            int iCheck = pSnake->paSnakeBody[i].iDirection;

            if ((iCheck == 0 && iDirection == 2) ||
                (iCheck == 1 && iDirection == 3) ||
                (iCheck == 2 && iDirection == 0) ||
                (iCheck == 3 && iDirection == 1)) {
                iDirection = iCheck;
            }
        }

//        Move current body direction to next one and new to current.
        iNextBodyDirection = pSnake->paSnakeBody[i].iDirection;
        pSnake->paSnakeBody[i].iDirection = iDirection;

//        Check to wait one round for new spawned snake-part
        if (i == pSnake->iSnakeSize - 2) {
            if (pSnake->paSnakeBody[i].iX == pSnake->paSnakeBody[i + 1].iX &&
                pSnake->paSnakeBody[i].iY == pSnake->paSnakeBody[i + 1].iY) {
                bSkipLast = true;
            }
        }

//        Change coordinate depending on direction
        if (iDirection == 0) {
            pSnake->paSnakeBody[i].iY--;
        } else if (iDirection == 1) {
            pSnake->paSnakeBody[i].iX--;
        } else if (iDirection == 2) {
            pSnake->paSnakeBody[i].iY++;
        } else if (iDirection == 3) {
            pSnake->paSnakeBody[i].iX++;
        }

        if (bSkipLast) {
            i++;
        }

        iDirection = iNextBodyDirection;
    }

}

bool SnakeGame::checkCollision() {
    int iX = pSnake->paSnakeBody[0].iX;
    int iY = pSnake->paSnakeBody[0].iY;

//    Check for hitting wall
    if (iX < 0 || iX > GRIDSIZE - 1 || iY < 0 || iY > GRIDSIZE - 1) {
        return false;
    }

//    Check for hitting snake body
    for (int i = 1; i < pSnake->iSnakeSize; ++i) {
        if (pSnake->paSnakeBody[i].iX == iX && pSnake->paSnakeBody[i].iY == iY) {
            return false;
        }
    }

//    Check for eating food
    if (pFood->iX == iX && pFood->iY == iY) {
        pFood->bFoodOnBoard = false;
        pFood->iX = -1;
        pFood->iY = -1;
        extendSnake();
        iScore += 1;
        Serial.print(iScore);
    }

    return true;
}

void SnakeGame::extendSnake() {
    if (pSnake->iSnakeSize < pSnake->iSnakeMaxSize) {
        int iOldTail = pSnake->iSnakeSize - 1;
        int iNewTail = pSnake->iSnakeSize;
        pSnake->iSnakeSize++;

        pSnake->paSnakeBody[iNewTail].iX = pSnake->paSnakeBody[iOldTail].iX;
        pSnake->paSnakeBody[iNewTail].iY = pSnake->paSnakeBody[iOldTail].iY;
        pSnake->paSnakeBody[iNewTail].iDirection = -1;
    }
}

void SnakeGame::spawnSnake() {
    int x = 4;
    int y = 4;
    pSnake->paSnakeBody[pSnake->iSnakeSize].iX = x;
    pSnake->paSnakeBody[pSnake->iSnakeSize].iY = y;
    pSnake->paSnakeBody[pSnake->iSnakeSize].iDirection = 0;
    pSnake->iSnakeSize++;

    pSnake->paSnakeBody[pSnake->iSnakeSize].iX = x;
    pSnake->paSnakeBody[pSnake->iSnakeSize].iY = y + 1;
    pSnake->paSnakeBody[pSnake->iSnakeSize].iDirection = 0;
    pSnake->iSnakeSize++;
}

void SnakeGame::spawnFood() {
    if (pFood->bFoodOnBoard) return;

    bool bSpawningFood = true;
    bool bBadSpawnForFood = false;

    while (bSpawningFood) {
        int x = (int) random() % 9;
        int y = (int) random() % 9;

//        Check if spawn coordinates is free
        for (int i = 0; i < pSnake->iSnakeSize; ++i) {
            if (pSnake->paSnakeBody[i].iX == x && pSnake->paSnakeBody[i].iY == y) {
                bBadSpawnForFood = true;
            }
        }

        if (bBadSpawnForFood) {
            continue;
        }

        pFood->bFoodOnBoard = true;
        pFood->iX = x;
        pFood->iY = y;
        bSpawningFood = false;
    }

}

void SnakeGame::printAndSaveScore() {
    pMTftScreen->printScore(iScore);
    pMEprom->saveScore(iScore);
}

void SnakeGame::freeSnakeGame() const {
    free(pSnake->paSnakeBody);
    free(pSnake);
    free(pFood);
}