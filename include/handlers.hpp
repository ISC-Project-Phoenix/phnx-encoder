#pragma once

const float INTERVAL = 100000; //microseconds
const float GEAR_RATIO = 28.0/58.0; 
const float WHEEL_DIAMETER = 0.35; //meters
const float pi = 3.14; 

enum class Direction {
    CW,
    CCW
};

struct message{
    uint8_t type; 
    uint16_t len; 
    uint8_t data[512];
} __attribute__((packed));

class Encoder {

    uint8_t chanA;
    uint8_t chanB;
    int64_t counter{};
    Direction dir;

public:
    float velocity; 
    uint16_t ticksSinceCAN; 
    const int64_t TICKS_PER_REV;
    Encoder(uint8_t chanA, uint8_t chanB) : chanA(chanA), chanB(chanB), dir(Direction::CW), TICKS_PER_REV(600), velocity(0.0), ticksSinceCAN(0){}

    int64_t tick() {
        auto aState = digitalRead(chanA);

        // if the Direction State is different from the Tick State
        if (digitalRead(chanB) != aState) {
            counter--; //Encoder is moved one Tick in CCW direction
            dir = Direction::CCW;
        } else {//Otherwise, Encoder moved ointellne Tick in CW direction
            counter++;
            dir = Direction::CW;
        }

        return counter;
    }

    int64_t getCounter(){
        return counter; 
    }

    Direction getDir() {
        return dir;
    }


};