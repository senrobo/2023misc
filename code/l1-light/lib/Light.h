#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <Common.h>

#include <Math.h>
#include <MyTimer.h>
#include <Pins.h>

// microseconds between each channel switch
#define MUX_DELAY 100

// class to control light sensors
class Light
{
public:
    void calibrate();
    void begin(uint8_t id);
    void read();
    void readRaw();
    void printLight();
    void printThresh();
    void sendVals();
    void getLineData(LineData &data);
    float lineTrack(float target);
    float getClosestAngle(float angle);
    bool doneReading();

        float lineAngle = 0;
    float lineTrackAngle;
    float lastLineAngle = 0;
    float initialLineAngle = 0;
    float chordLength = 0;
    bool onLine = false;
    int lineDetected[32];
    int outSensors = 0;
    float clusterStart;
    float clusterEnd;
    // mapping from light sensor position in MUX to position in circle
    int lightMap[32] = {25, 26, 27, 28, 29, 30, 1, 0, 31, 2, 3,
                        4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                        15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

    // int fixedThreshWhiteBot[32] = {224, 333, 372, 224, 388, 224, 398, 406,
    //                                224, 400, 391, 402, 336, 164, 224, 224,
    //                                224, 224, 224, 398, 391, 402, 336, 164,
    //                                224, 271, 224, 333, 224, 224, 224, 333};

    // int fixedThreshBlackBot[32] = {237, 362, 237, 258, 258, 258, 258, 327,
    //                                258, 259, 327, 340, 258, 358, 259, 361,
    //                                327, 258, 237, 258, 258, 258, 258, 258,
    //                                258, 258, 258, 258, 258, 258, 258, 259};

    // SCIENCE CENTRE VALS
    int fixedThreshBlackBot[32] = {313, 325, 234, 307, 258, 258, 309, 256,
                                   313, 325, 234, 258, 258, 256, 322, 325,
                                   234, 233, 258, 234, 258, 258, 256, 313,
                                   234, 325, 233, 234, 258, 258, 258, 256};

    int fixedThreshWhiteBot[32] = {456, 380, 457, 409, 449, 450, 460, 465,
                                   456, 380, 406, 409, 450, 456, 457, 380,
                                   457, 406, 409, 456, 404, 403, 380, 456,
                                   380, 450, 380, 380, 406, 380, 409, 380};

    int muxChannel[16][4] = {
        {0, 0, 0, 0}, // channel 0
        {1, 0, 0, 0}, // channel 1
        {0, 1, 0, 0}, // channel 2
        {1, 1, 0, 0}, // channel 3
        {0, 0, 1, 0}, // channel 4
        {1, 0, 1, 0}, // channel 5
        {0, 1, 1, 0}, // channel 6
        {1, 1, 1, 0}, // channel 7
        {0, 0, 0, 1}, // channel 8
        {1, 0, 0, 1}, // channel 9
        {0, 1, 0, 1}, // channel 10
        {1, 1, 0, 1}, // channel 11
        {0, 0, 1, 1}, // channel 12
        {1, 0, 1, 1}, // channel 13
        {0, 1, 1, 1}, // channel 14
        {1, 1, 1, 1}  // channel 15
    };
    LightBuffer lightThresh;
    LightBuffer lightBuffer;
    LineData lineData;
    int lightVals[32];
    int maxVals[32];
    int minVals[32];
    long readTimer = 0;
    int lightCnt = 0;
};

#endif