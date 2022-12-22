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
    Direction dir;

public:
    Encoder(uint8_t chanA, uint8_t chanB) : chanA(chanA), chanB(chanB), dir(Direction::CW), TICKS_PER_REV(600){}

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
        int64_t displacement = counter - prevCounter;
        int64_t enc_rev = displacement / TICKS_PER_REV;
        // enc_rev * 
        return 0;
    }

    Direction getDir() {
        return dir;
    }
};