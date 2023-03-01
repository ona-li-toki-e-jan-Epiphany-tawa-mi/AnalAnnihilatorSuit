# 1 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
/**

 * This is the program code responsible for running the microcontroller brain of the suit.

 * @attention ATMega2560

 * 

 * @author ona li toki e jan Epiphany tawa mi.

 */
# 8 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
/**

 * Red PWM pin of the arc reactor's LEDs.

 */
# 12 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
/**

 * Green PWM pin of the arc reactor's LEDs.

 */
# 16 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
/**

 * Blue PWM pin of the arc reactor's LEDs.

 */
/**

 * Data and code regarding the arc-reactor-like LED array on the front of the suit.

 */
# 24 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
namespace arcReactor {
    uint8_t columnPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
    uint8_t columns = 8;
    uint8_t rowPins[] = {30, 31, 32, 33, 34, 35, 36};
    uint8_t rows = 7;

    void initialize() {
        for (uint8_t pin : arcReactor::columnPins)
            pinMode(pin, 0x1);
        for (uint8_t pin : arcReactor::rowPins)
            pinMode(pin, 0x1);

        pinMode(12, 0x1);
        pinMode(11, 0x1);
        pinMode(10, 0x1);;
    }

    /**

     * A buffer used to store the colors that the arc reactor should display.

     */
# 44 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
    uint32_t displayBuffer[60] = {0};

    /**

     * Outputs the color data stored in the buffer to the LED array.

     * @attention This needs to be called constantly in a loop to keep up the display.

     */
# 50 "/home/stariki/Proyekty/PROGRAMMY/AnalAnnihilatorSuit/AnalAnnihilatorSuit.ino"
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
                    digitalWrite(previousColumnPin, 0x0);
                    digitalWrite(previousRowPin, 0x0);
                }

                digitalWrite(12, red);
                digitalWrite(11, blue);
                digitalWrite(10, green);
                // Selects LED to output to.
                previousColumnPin = columnPins[column];
                digitalWrite(previousColumnPin, 0x1);
                previousRowPin = rowPins[row];
                digitalWrite(previousRowPin, 0x1);
            }

        // Unselect final pin.
        digitalWrite(previousColumnPin, 0x0);
        digitalWrite(previousRowPin, 0x0);
    }
}

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
