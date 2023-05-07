#include "MEeprom.h"

MEeprom::MEeprom() {
//    nDevice is how many eeproms that are on that address
//    pageSize is in bytes
//    eepromAddr is address in bytes
    pEprom = new extEEPROM(kbits_256, 1, 64, 0x57);
}

void MEeprom::test() {
    pEprom->begin();
    pEprom->write(0x00, 10);
    pEprom->write(0x01, 30);
    pEprom->write(0x02, 50);
    pEprom->write(0x03, 70);
    pEprom->write(0x04, 80);

    int iNumber1 = pEprom->read(0x00);
    int iNumber2 = pEprom->read(0x01);
    int iNumber3 = pEprom->read(0x02);
    int iNumber4 = pEprom->read(0x03);
    int iNumber5 = pEprom->read(0x04);

    Serial.println(iNumber1);
    Serial.println(iNumber2);
    Serial.println(iNumber3);
    Serial.println(iNumber4);
    Serial.println(iNumber5);
}

void MEeprom::clearMemory() {
    pEprom->begin();
    for (int i = 0; i < 100; ++i) {
        int error = pEprom->write(i, 0);
    }
}

void MEeprom::saveScore(int iScore) {
    int aiScores[HIGH_SCORE_SIZE] = {0};

    pEprom->begin();
//    get high scores
    for (int i = 0; i < HIGH_SCORE_SIZE; ++i) {
        aiScores[i] = pEprom->read(i);
    }

//    sort high scores
    for (int i = 0; i < HIGH_SCORE_SIZE; ++i) {
        if (iScore >= aiScores[i] && i < (HIGH_SCORE_SIZE - 1)) {
            int iTmp = aiScores[i];
            aiScores[i] = iScore;
            iScore = iTmp;
        }
    }

//    save new high scores
    for (int i = 0; i < HIGH_SCORE_SIZE; ++i) {
        pEprom->write(i, aiScores[i]);
    }

}

int *MEeprom::getHighScoreTable() {
    int *aiScores = (int *) calloc(HIGH_SCORE_SIZE, sizeof(int));

    pEprom->begin();
    for (int i = 0; i < HIGH_SCORE_SIZE; ++i) {
        aiScores[i] = pEprom->read(i);
        Serial.println(aiScores[i]);
    }

    return aiScores;
}
