#ifndef SNAKEBACKEND_SNAKEGAME_H
#define SNAKEBACKEND_SNAKEGAME_H

#include "../modules/MTftScreen.h"
#include "../modules/MGyroscope.h"
#include "../modules/MEeprom.h"
#include "SnakeIO.h"
#include "SnakeEnumAndStructs.h"

#include <Arduino.h>

/* Snake board have 135px * 135px
 * Size of each square is 15px * 15px
 * Meaning total squares on the screen is 9 * 9 */
#define GRIDSIZE 9

class SnakeGame {
public:
    /* Constructor that initialise every heap memory dependent elements*/
    SnakeGame(MGyroscope *pMGyroscope, MTftScreen *pMTftScreen, MEeprom *pMEprom);

    /* Starts the game loop*/ // TODO might remove this on arduino
    void startGame();

    /* Free allocated memory, will be used if I know how to turn off and on the arduino */
    void freeSnakeGame() const;

private:
    /* Changes coordinates for each body part making the snake move*/
    void moveSnake(int iDirection);

    /* Checks what snake head is meeting in the new coordinates
     * RETURN       True if snake is still alive or
     *              False if snake is dead */
    bool checkCollision();

    /* Spawns snakes randomly on the board, will always start moving upward as default*/
    void spawnSnake();

    /* Checks if there is food on the table first, of not spawn food randomly */
    void spawnFood();

    /* When snake eats food, it needs to grow by one */
    void extendSnake();

    /* Prints out score screen and saves score high score if high enough */
    void printAndSaveScore();

    int iScore;
    Snake *pSnake;
    Food *pFood;
    SnakeIO *pSnakeIO;
    MTftScreen *pMTftScreen;
    MEeprom *pMEprom;
};


#endif //SNAKEBACKEND_SNAKEGAME_H
