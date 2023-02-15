#include "Light.h"

void Light::begin()
{

    pinMode(mux_A1, OUTPUT);
    pinMode(mux_A2, OUTPUT);
    pinMode(mux_A3, OUTPUT);
    pinMode(mux_A4, OUTPUT);

    pinMode(mux_B1, OUTPUT);
    pinMode(mux_B2, OUTPUT);
    pinMode(mux_B3, OUTPUT);
    pinMode(mux_B4, OUTPUT);

    digitalWriteFast(mux_A1, LOW);
    digitalWriteFast(mux_A2, LOW);
    digitalWriteFast(mux_A3, LOW);
    digitalWriteFast(mux_A4, LOW);

    digitalWriteFast(mux_B1, LOW);
    digitalWriteFast(mux_B2, LOW);
    digitalWriteFast(mux_B3, LOW);
    digitalWriteFast(mux_B4, LOW);
}
void Light::printThresh()
{
    L1DebugSerial.print("Thresh: ");
    for (int i = 0; i < 32; i++)
    {
        L1DebugSerial.print(lightThresh.vals[i]);
        L1DebugSerial.print(", ");
    }
    L1DebugSerial.println();
}

void Light::printLight()
{
    L1DebugSerial.print("Values: ");
    for (int i = 0; i < 32; i++)
    {
        L1DebugSerial.print(lightVals[i]);
        L1DebugSerial.print(", ");
    }
    L1DebugSerial.println();
}

void Light::readRaw()
{
    // no mapping
    if (micros() - readTimer >= 100)
    {
        bool out = false;
        // read from first MUX
        int idx = lightCnt;

        lightVals[idx] = analogRead(sigA);
        // if (lightVals[idx] > lightThresh.vals[idx]) {
        //     lineDetected[outSensors] = idx;
        //     outSensors++;
        // }
        // // read from second MUX
        idx = lightCnt + 16;

        // lightVals[idx] = analogRead(sigB);
        // if (lightVals[idx] > lightThresh.vals[idx]) {
        //     lineDetected[outSensors] = idx;
        //     outSensors++;
        // }

        lightCnt++;
        lightCnt %= 16;
        // delayMicroseconds(100);
        digitalWriteFast(mux_A1, muxChannel[lightCnt][0]);
        digitalWriteFast(mux_A2, muxChannel[lightCnt][1]);
        digitalWriteFast(mux_A3, muxChannel[lightCnt][2]);
        digitalWriteFast(mux_A4, muxChannel[lightCnt][3]);

        // digitalWriteFast(mux_B1, muxChannel[lightCnt][0]);
        // digitalWriteFast(mux_B2, muxChannel[lightCnt][1]);
        // digitalWriteFast(mux_B3, muxChannel[lightCnt][2]);
        // digitalWriteFast(mux_B4, muxChannel[lightCnt][3]);

        readTimer = micros();
    }
}
void Light::read()
{
    // non blocking light read
    if (micros() - readTimer >= 70)
    {
        bool out = false;
        // read from first MUX
        int idx = lightMap[lightCnt];

        lightVals[idx] = analogRead(sigA);

        if (lightVals[idx] > lightThresh.vals[idx] && ((idx != 25 && robotID == 1) || robotID == 0))
        {
            lineDetected[outSensors] = idx;
            outSensors++;
        }
        // read from second MUX
        idx = lightMap[lightCnt + 16];

        lightVals[idx] = analogRead(sigB);
        if (lightVals[idx] > lightThresh.vals[idx] && ((idx != 25 && robotID == 1) || robotID == 0))
        {
            lineDetected[outSensors] = idx;
            outSensors++;
        }

        lightCnt++;
        lightCnt %= 16;
        // delayMicroseconds(100);
        digitalWriteFast(mux_A1, muxChannel[lightCnt][0]);
        digitalWriteFast(mux_A2, muxChannel[lightCnt][1]);
        digitalWriteFast(mux_A3, muxChannel[lightCnt][2]);
        digitalWriteFast(mux_A4, muxChannel[lightCnt][3]);

        digitalWriteFast(mux_B1, muxChannel[lightCnt][0]);
        digitalWriteFast(mux_B2, muxChannel[lightCnt][1]);
        digitalWriteFast(mux_B3, muxChannel[lightCnt][2]);
        digitalWriteFast(mux_B4, muxChannel[lightCnt][3]);

        readTimer = micros();
    }
}

bool Light::doneReading()
{
    // all sensors have been read once lightCnt goes back to 0

    return lightCnt == 0;
}

void Light::sendVals()
{
    L1CommSerial.write(LAYER1_SEND_SYNC_BYTE);
    for (int i = 0; i < 32; i++)
    {
        lightBuffer.vals[i] = lightVals[i];
        L1CommSerial.write(lightBuffer.b, 2);
    }
}

void Light::calibrate()
{
#ifdef DEBUG
    L1DebugSerial.print("Calibrating...");
#endif
    // reset max and min values each time
    for (int i = 0; i < 32; i++)
    {
        maxVals[i] = 0;
        minVals[i] = 1200;
    }
    const unsigned long timeOut = 60000;
    unsigned long timeStart = millis();
    while (true)
    {
        // L1DebugSerial.println("Calibrating...");

        read();
        if (doneReading())
        {
            // L1DebugSerial.print("Min: ");
            // for (int i = 0; i < 32; i++) {
            //     L1DebugSerial.print(minVals[lightMap[i]]);
            //     L1DebugSerial.print(" ");
            // }
            // L1DebugSerial.println();
            // L1DebugSerial.print("Thresh: ");
            // for (int i = 0; i < 32; i++) {
            //     L1DebugSerial.print(lightThresh.vals[lightMap[i]]);
            //     L1DebugSerial.print(" ");
            // }
            // L1DebugSerial.println();
            for (auto i : lightMap)
            {
                if (lightVals[i] > maxVals[i])
                {
                    maxVals[i] = lightVals[i];
                }
                if (lightVals[i] < minVals[i])
                {
                    minVals[i] = lightVals[i];
                }

                lightThresh.vals[i] = (maxVals[i] + minVals[i]) / 2;
            }
            L1DebugSerial.print("Max: ");
            for (int i = 0; i < 32; i++)
            {
                L1DebugSerial.print(maxVals[lightMap[i]]);
                L1DebugSerial.print(" ");
            }
            L1DebugSerial.println();
            L1DebugSerial.print("Min: ");
            for (int i = 0; i < 32; i++)
            {
                L1DebugSerial.print(minVals[lightMap[i]]);
                L1DebugSerial.print(" ");
            }
            L1DebugSerial.println();
            L1DebugSerial.print("Thresh: ");
            for (int i = 0; i < 32; i++)
            {
                L1DebugSerial.print(lightThresh.vals[lightMap[i]]);
                L1DebugSerial.print(", ");
            }
            L1DebugSerial.println();
        }

        // printLight();
    }
#ifdef DEBUG
    L1DebugSerial.print("Done!");
#endif

#ifdef DEBUG

    while (true)
    {
        L1DebugSerial.print("Max: ");
        for (int i = 0; i < 32; i++)
        {
            L1DebugSerial.print(maxVals[lightMap[i]]);
            L1DebugSerial.print(" ");
        }
        L1DebugSerial.println();
        L1DebugSerial.print("Min: ");
        for (int i = 0; i < 32; i++)
        {
            L1DebugSerial.print(minVals[lightMap[i]]);
            L1DebugSerial.print(" ");
        }
        L1DebugSerial.println();
        L1DebugSerial.print("Thresh: ");
        for (int i = 0; i < 32; i++)
        {
            L1DebugSerial.print(lightThresh.vals[lightMap[i]]);
            L1DebugSerial.print(", ");
        }
        L1DebugSerial.println();
    }

#endif

#ifdef USE_EEPROM
    // write calibrated threshold to eeprom memory
    for (auto i : lightMap)
    {
        eeprom_buffered_write_byte(i + 1, lightThresh.b[i * 2]);
        eeprom_buffered_write_byte(i + 33, lightThresh.b[i * 2 + 1]);
    }
    eeprom_buffer_flush();

#endif

    L1CommSerial.write(LAYER1_SEND_SYNC_BYTE);
    // send thresholds to teensy for checking
    for (int i = 0; i < 32; i++)
    {
        L1CommSerial.write(lightThresh.b, 2);
    }
}

// TO DO: WRITE CALIBRATED LIGHT VALS TO STM32 EEPROM MEMORY

void Light::getLineData(LineData &data)
{
    float vecX = 0;
    float vecY = 0;
    clusterStart = -1;
    clusterEnd = -1;
    float largestDiff = 0;
    bool previouslyOnLine = onLine;
    float closestAngle = 0;
    onLine = outSensors > 0;
    if (onLine)
    {
        // for (int i = 0; i < outSensors; i++) {
        //     int tmp = lineDetected[i];
        //     L1DebugSerial.print(tmp);
        //     L1DebugSerial.print(": ");
        //     L1DebugSerial.print(lightVals[tmp]);
        //     L1DebugSerial.print(": ");
        //     L1DebugSerial.print(lightThresh.vals[tmp]);
        //     L1DebugSerial.print(", ");

        // }
        // L1DebugSerial.println();
        // get line angle and chord length
        if (outSensors == 1)
        {
            onLine = false;
        }
        else
        {
            for (int i = 0; i < outSensors - 1; i++)
            {
                for (int j = 1; j < outSensors; j++)
                {
                    float tmpDiff = angleDiff(lineDetected[i] * (360 / 32),
                                              lineDetected[j] * (360 / 32));
                    if (tmpDiff > largestDiff)
                    {
                        clusterStart = lineDetected[i] * (360 / 32);
                        clusterEnd = lineDetected[j] * (360 / 32);
                        largestDiff = tmpDiff;
                    }
                }
            }

            chordLength = angleDiff(clusterStart, clusterEnd) / 180;
            lineAngle = angleBetween(clusterStart, clusterEnd) <= 180
                            ? midAngleBetween(clusterStart, clusterEnd)
                            : midAngleBetween(clusterEnd, clusterStart);
        }
    }
    outSensors = 0;

    // update data
    data.onLine = onLine;
    data.lineAngle.val = lineAngle;
    data.chordLength.val = chordLength;

    // save initial line angle
    if (onLine && !previouslyOnLine)
    {
        data.initialLineAngle.val = lineAngle;
    }
    lineTrackAngle = closestAngle;
}
float Light::getClosestAngle(float angle)
{
    if (angleDiff(angle, clusterStart) < angleDiff(angle, clusterEnd))
    {
        return clusterStart;
    }
    else
    {
        return clusterEnd;
    }
}