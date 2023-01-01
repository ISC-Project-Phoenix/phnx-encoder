#include <Arduino.h>
#include <handlers.hpp>

/// Changes state when encoder moves 1 Tick
constexpr uint8_t TICK_CH_A_PIN = 23;
/// State relative to Channel A determines direction of Encoder, CW or CCW
constexpr uint8_t DIR_CH_B_PIN = 22;

IntervalTimer findVel;

static bool tickToRead = false;
static bool msgToSend = false; 
static int64_t prevCounter = 0;
Encoder encoder{TICK_CH_A_PIN, DIR_CH_B_PIN};

void onChanATick() {
    Serial.print("Waking...");
    tickToRead = true;
    //Wake loop
    asm volatile ("sev"); 
}

void calcVel(){//calculated per 0.1 second time intervals
    auto curCount = encoder.getCounter();
    auto displacement = curCount - prevCounter; // displacement in Ticks
    float distance = (displacement * pi * WHEEL_DIAMETER)/ (encoder.TICKS_PER_REV * GEAR_RATIO);
    //distance covered in 0.1 seconds interval
    //distance in meters
    //velocity in meters per second
    encoder.velocity = (distance * 10); 
    msgToSend = true; 
    prevCounter = curCount; 
}


void setup() {
    pinMode(TICK_CH_A_PIN, INPUT_PULLUP);
    pinMode(DIR_CH_B_PIN, INPUT);
    Serial.begin(9600);
    findVel.begin(calcVel, INTERVAL);
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
