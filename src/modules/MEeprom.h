#ifndef PG550_EXAM_ESP32_MEEPROM_H
#define PG550_EXAM_ESP32_MEEPROM_H

#include "extEEPROM.h"

#define HIGH_SCORE_SIZE 5

class MEeprom {
public:
    /* Constructor that is hardcoded for EEPROM 24C32 */
    MEeprom();

    /* Test to write and read from EEPROM, using Serial */
    void test();

    /* Reset all the memory to value 0 */
    void clearMemory();

    /* Saves the score of the user, it checks the existing ones and
     * saves it in the correct order
     * PARA1        int value score from user */
    void saveScore(int iScore);

    /* Get the high score table (5 values)
     * RETURN       pointer int array with high scores */
    int *getHighScoreTable();

private:
    extEEPROM *pEprom;
};


#endif //PG550_EXAM_ESP32_MEEPROM_H
