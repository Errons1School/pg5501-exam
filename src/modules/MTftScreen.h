#ifndef PG550_EXAM_MTFTSCREEN_H
#define PG550_EXAM_MTFTSCREEN_H

#include "../snake/SnakeEnumAndStructs.h"
#include "Adafruit_ImageReader.h"
#include "MPotentiometer.h"

#include <Adafruit_ST7789.h>

#define INT_GRID_SIZE_Y 135
#define INT_GRID_SIZE_X 240
#define INT_GAME_PIXEL 15
#define INT_HIGH_SCORE_SIZE 5

class MTftScreen {
public:
    /* Constructor to wrapper class for tft and sd module
     * PARA1        int value for pin used for slave select
     * PARA2        int value for pin used for data controller TFT
     * PARA3        int value for pin used for data controller SD */
    MTftScreen(int slaveSelect, int dataControllerTft, int dataControllerSD);

    /* Simple test to change screen color and print text */
    void screenTest();

    /* Simple test to print texture from SD card to TFT */
    void testTexture();

    /* Clears screen and make it "light" black */
    void clearScreen();

    /* With correct arguments prints out a picture from SD card on wished location
     * PARA1        int value that indicates what to print
     * PARA2        int value of X coordinate on TFT to print on
     * PARA3        int value of Y coordinate on TFT to print on
     * PARA4        int value that indicates what direction the image should be printed on*/
    void printTexture(int iWhatToPrint, int iX, int iY, int iDirection);

    /* Prints the main menu with non or one option highlighted
     * PARA1        int value of what menu option to highlight */
    void printMainMenu(int iOption);

    /* Prints an end of game screen with players score
     * PARA1        int value of players score */
    void printScore(int iScore);

    /* Prints a screen of the high scores that player have gotten
     * PARA1        pointer int array of high scores */
    void printHighScore(int *aiScores);

    /* Prints the whole screen filled with background grass */
    void printBackgroundGrass();

private:
    Adafruit_ST7789 *pTft;
    SdFat *pSD;
    Adafruit_ImageReader *pReader;
};


#endif //PG550_EXAM_MTFTSCREEN_H
