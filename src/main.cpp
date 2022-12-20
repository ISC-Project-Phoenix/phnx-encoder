#include <Arduino.h>
#include <handlers.hpp>

/// Changes state when encoder moves 1 Tick
constexpr uint8_t TICK_CH_A_PIN = 23;
/// State relative to Channel A determines direction of Encoder, CW or CCW
constexpr uint8_t DIR_CH_B_PIN = 22;

static bool tickToRead = false;
Encoder encoder{TICK_CH_A_PIN, DIR_CH_B_PIN};

void onChanATick() {
    Serial.print("Waking...");
    tickToRead = true;
    //Wake loop
    asm volatile ("sev");
}

void setup() {
    pinMode(TICK_CH_A_PIN, INPUT_PULLUP);
    pinMode(DIR_CH_B_PIN, INPUT);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(TICK_CH_A_PIN), &onChanATick, CHANGE);
}

void loop() {
    if (tickToRead) {
        auto count = encoder.tick();
        auto currentDir = encoder.getDir();

        // Print Direction and Counter when Encoder moves 1 Tick
        Serial.print("Direction: ");
        if (currentDir == Direction::CW) {
            Serial.print("CW");
        } else {
            Serial.print("CCW");
        }
        Serial.print(" | Counter: ");
        Serial.println(count);
    }
    Serial.print("Sleeping...");
    asm volatile ("wfe");
}
