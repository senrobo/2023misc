#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"

// STM32 Pinouts
#define mux1 PB0
#define mux2 PB7
#define m1s0 PB1
#define m1s1 PB2
#define m1s2 PA6
#define m1s3 PA5
#define m2s0 PB8
#define m2s1 PB9
#define m2s2 PB6
#define m2s3 PB5
#define sol PB10
#define led PC13

// microseconds between each channel switch
#define MUX_DELAY 70

// Initilalize Variables
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

int lightVals[30];
int maxVals[30];
int minVals[30];
long readTimer = 0;
int lightCnt = 0;

int fixedThreshFirstBot[30] = {224, 333, 372, 224, 388, 224, 398, 406, 224, 400, 391, 402, 336, 164, 224, 224, 224, 224, 224, 398, 391, 402, 336, 164, 224, 271, 224, 333, 224, 224};

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

#endif
