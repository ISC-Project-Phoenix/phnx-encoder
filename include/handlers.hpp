#pragma once

enum class Direction {
    CW,
    CCW
};

class Encoder {

    uint8_t chanA;
    uint8_t chanB;
    int64_t counter{};
    int64_t prevCounter{};
    const int64_t TICKS_PER_REV;
    const int64_t INTERVAL; //miliseconds 
    const float GEAR_RATIO; 
    Direction dir;

public:
    Encoder(uint8_t chanA, uint8_t chanB) : chanA(chanA), chanB(chanB), dir(Direction::CW), TICKS_PER_REV(600), INTERVAL(100), GEAR_RATIO(28/58){}

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

    float calcVel(){
        int64_t displacement = counter - prevCounter; // displacement in Ticks
        float enc_rev = displacement / TICKS_PER_REV; // # of encoder revolutions
        float rpm = enc_rev * GEAR_RATIO * 10 * 60; // per second * 60 seconds in a minute
        return rpm;
    }

    void getCurrentTick(int64_t currentTick){
        prevCounter = counter;
        counter = currentTick; 
    }

    Direction getDir() {
        return dir;
    }
};