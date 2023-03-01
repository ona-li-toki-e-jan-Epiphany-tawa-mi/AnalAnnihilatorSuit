#include <Arduino.h>
#line 1 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
/**
 * This is the program code responsible for running the microcontroller brain of the suit.
 * @attention ATMega2560
 * 
 * @author ona li toki e jan Epiphany tawa mi.
 */

/**
 * Red PWM pin of the arc reactor's LEDs.
 */
#define ARC_REACTOR_RED_PIN 12
/**
 * Green PWM pin of the arc reactor's LEDs.
 */
#define ARC_REACTOR_GREEN_PIN 11
/**
 * Blue PWM pin of the arc reactor's LEDs.
 */
#define ARC_REACTOR_BLUE_PIN 10

/**
 * Data and code regarding the arc-reactor-like LED array on the front of the suit.
 */
namespace arcReactor {
    uint8_t columnPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
    uint8_t columns = 8;
    uint8_t rowPins[] = {30, 31, 32, 33, 34, 35, 36}; 
    uint8_t rows = 7;

    void initialize() {
        for (uint8_t pin : arcReactor::columnPins)
            pinMode(pin, OUTPUT);
        for (uint8_t pin : arcReactor::rowPins)
            pinMode(pin, OUTPUT);

        pinMode(ARC_REACTOR_RED_PIN,   OUTPUT);
        pinMode(ARC_REACTOR_GREEN_PIN, OUTPUT);
        pinMode(ARC_REACTOR_BLUE_PIN,  OUTPUT);;
    }

    /**
     * A buffer used to store the colors that the arc reactor should display.
     */
    uint32_t displayBuffer[60] = {0};

    /**
     * Outputs the color data stored in the buffer to the LED array.
     * @attention This needs to be called constantly in a loop to keep up the display.
     */
    void outputBuffer() {
        uint8_t previousColumnPin = -1
              , previousRowPin = -1;

        for (uint8_t column = 0; column < columns; column++)
            for (uint8_t row = 0; row < rows; row++) {
                uint32_t color = arcReactor::displayBuffer[column * rows + row];
                uint8_t red = (color & 0xFF0000) >> 16;
                uint8_t blue = (color & 0x00FF00) >> 8;
                uint8_t green = color & 0x0000FF;

                // Unselects previous LED.
                if (previousColumnPin != -1) {
                    digitalWrite(previousColumnPin, LOW);
                    digitalWrite(previousRowPin, LOW);
                }

                digitalWrite(ARC_REACTOR_RED_PIN, red);
                digitalWrite(ARC_REACTOR_GREEN_PIN, blue);
                digitalWrite(ARC_REACTOR_BLUE_PIN, green);
                // Selects LED to output to.
                previousColumnPin = columnPins[column];
                digitalWrite(previousColumnPin, HIGH);
                previousRowPin = rowPins[row];
                digitalWrite(previousRowPin, HIGH);
            }

        // Unselect final pin.
        digitalWrite(previousColumnPin, LOW);
        digitalWrite(previousRowPin, LOW);
    }
}

#line 83 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
void setup();
#line 90 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
void loop();
#line 83 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
void setup() {
	arcReactor::initialize();
}

uint8_t snake = 0;
uint32_t color = 0xFF0000;

void loop() {
	arcReactor::outputBuffer();

    arcReactor::displayBuffer[snake] = color;

    if (++snake >= 60) {
        snake = 0;
        color = color == 0xFF0000 ? 0x0000FF : 0xFF0000;
    }
}

