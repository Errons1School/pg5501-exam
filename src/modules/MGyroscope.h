#ifndef PG550_EXAM_MGYROSCOPE_H
#define PG550_EXAM_MGYROSCOPE_H

#include <GY521.h>
#include <Wire.h>


class MGyroscope {
public:
    /* Constructor that have hardcoded values for GY-521 */
    MGyroscope();

    /* Methode to print out the different values from gyroscope */
    void serialPrintTest();

    /* A gyroscope check to se if user have done a squat for selecting
     * RETURN       int value 1 if selected or 0 if not selected */
    int getSelect();

    /* A gyroscope check to se if user have turned left or right
     * RETURN       int value 1 left, -1 right and 0 not moved */
    int getLeftOrRight();

private:
    GY521 *pGyro;
    float fAccX = 0;
    float fGyroZ = 0;
};


#endif //PG550_EXAM_MGYROSCOPE_H
