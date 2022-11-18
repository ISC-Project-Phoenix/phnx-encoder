#pragma once

enum class Direction {
    CW,
    CCW
};

class Encoder {

    uint8_t chanA;
    uint8_t chanB;
    int64_t counter{};
    Direction dir;

public:
    Encoder(uint8_t chanA, uint8_t chanB) : chanA(chanA), chanB(chanB), dir(Direction::CW) {}

    int64_t tick() {
        auto aState = digitalRead(chanA);

        // if the Direction State is different from the Tick State
        if (digitalRead(chanB) != aState) {
            counter--; //Encoder is moved one Tick in CCW direction
            dir = Direction::CCW;
        } else {//Otherwise, Encoder moved one Tick in CW direction
            counter++;
            dir = Direction::CW;
        }

        return counter;
    }

    Direction getDir() {
        return dir;
    }
};