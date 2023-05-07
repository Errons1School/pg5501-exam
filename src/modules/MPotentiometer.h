#ifndef PG550_EXAM_ESP32_MPOTENTIOMETER_H
#define PG550_EXAM_ESP32_MPOTENTIOMETER_H


class MPotentiometer {
public:
    /* Constructor with dynamic pin for using a Potentiometer
     * PARA1        int value pin number using to read analog value */
    explicit MPotentiometer(int iPinPotentiometerReader);

    /* Checks current value with old to se if user scrolled up or down
     * RETURN       int value 1 up or -1 down */
    int getUpOrDown();

private:
    int iPinPotentiometerReader;
    int iPotentiometerValue;
};


#endif //PG550_EXAM_ESP32_MPOTENTIOMETER_H
