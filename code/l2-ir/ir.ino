void initIR() // Initialize IR set all pins to high
{
    pinMode(17, INPUT); // 1
    pinMode(16, INPUT); // 2
    pinMode(15, INPUT); // 3
    pinMode(14, INPUT); // 4
    pinMode(11, INPUT); // 5
    pinMode(10, INPUT); // 6
    pinMode(46, INPUT); // 7
    pinMode(45, INPUT); // 8
    pinMode(43, INPUT); // 9
    pinMode(42, INPUT); // 10
    pinMode(41, INPUT); // 11
    pinMode(40, INPUT); // 12
    pinMode(39, INPUT); // 13
    pinMode(38, INPUT); // 14
    pinMode(29, INPUT); // 15
    pinMode(28, INPUT); // 16
    pinMode(27, INPUT); // 17
    pinMode(26, INPUT); // 18
    pinMode(25, INPUT); // 19
    pinMode(22, INPUT); // 20
    pinMode(21, INPUT); // 21
    pinMode(20, INPUT); // 22
    pinMode(19, INPUT); // 23
    pinMode(18, INPUT); // 24
}

void readIR(int n)
{
    for (int i = 0; i < n; i++)
    {
        tempValues[0] += digitalReadFast(17) ^ 1; // bitwise function: +1 to digitalread value everytime so it will be 1,2,3,4,5...
        tempValues[1] += digitalReadFast(16) ^ 1;
        tempValues[2] += digitalReadFast(15) ^ 1;
        tempValues[3] += digitalReadFast(14) ^ 1;
        tempValues[4] += digitalReadFast(11) ^ 1;
        tempValues[5] += digitalReadFast(10) ^ 1;
        tempValues[6] += digitalReadFast(46) ^ 1;
        tempValues[7] += digitalReadFast(45) ^ 1;
        tempValues[8] += digitalReadFast(43) ^ 1;
        tempValues[9] += digitalReadFast(42) ^ 1;
        tempValues[10] += digitalReadFast(41) ^ 1;
        tempValues[11] += digitalReadFast(40) ^ 1;
        tempValues[12] += digitalReadFast(39) ^ 1;
        tempValues[13] += digitalReadFast(38) ^ 1;
        tempValues[14] += digitalReadFast(29) ^ 1;
        tempValues[15] += digitalReadFast(28) ^ 1;
        tempValues[16] += digitalReadFast(27) ^ 1;
        tempValues[17] += digitalReadFast(26) ^ 1;
        tempValues[18] += digitalReadFast(25) ^ 1;
        tempValues[19] += digitalReadFast(22) ^ 1;
        tempValues[20] += digitalReadFast(21) ^ 1;
        tempValues[21] += digitalReadFast(20) ^ 1;
        tempValues[22] += digitalReadFast(19) ^ 1;
        tempValues[23] += digitalReadFast(18) ^ 1;
    }

    tsspCounter++; //+1 to counter to count the no. of times it read
}

void processIR()
{
    // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
    for (int i = 0; i < 23; i++)
    {
        values[i] = 100 * (double)tempValues[i] / (double)tsspCounter; // calculate the average value of the sensor
        tempValues[i] = 0;                                             // reset the temp values
        sortedValues[i] = 0;
        indexes[i] = 0;
        tsspCounter = 0;
    }

    IRsortvalues();
    IRcalculateanglestrength(TSOP_BEST_TSOP_NUMBER);
}

void IRsortvalues()
{
    // Sort the TSOP values from greatest to least in sortedFilteredValues
    // and sort the TSOP indexes from greatest to least strength in indexes (array positions)

    for (uint8_t i = 0; i < TSOP_NUM; i++)
    {
        for (uint8_t j = 0; j < TSOP_NUM; j++)
        {
            if (values[i] > sortedValues[j])
            {
                // We've found our place!
                // Shift elements from index j down
                if (j <= i)
                {
                    // Make sure we only shift what is needed
                    ARRAYSHIFTDOWN(sortedValues, j, i); // sort strength from weakest to strongest in the array
                    ARRAYSHIFTDOWN(indexes, j, i);      // sort the indexes
                }

                sortedValues[j] = values[i];
                indexes[j] = i;
                break;
            }
        }
    }
}

void IRcalculateanglestrength(int n)
{
    // Cartesian addition of best n TSOPs
    float s = 0;
    float t = 0;
    noValsCounter = 0;

    for (int i = 0; i < 16; i++)
    {
        s += sortedValues[i];
        if (sortedValues[i] == 0)
        {
            noValsCounter++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        t += sortedValues[i];
    }
    strength = t / s; // calculate strength as a proportion number, between 0 and 1 ***check reliability
    if (loopcounter < 1)
    {

        if (s == 0)
        {
            angle = lastangle;
            // Serial.println("is there ball??");
            loopcounter++;
        }
        else
        {
            if (indexes[0] == 0 || indexes[1] == 0 || indexes[2] == 0)
            {
                if (sortedValues[0] > 60)
                {
                    angle = 0;
                    // Serial.println("front");
                }
                else
                {
                    angle = indexes[0] * 22.5;
                    lastangle = angle;
                    // Serial.println("haha");
                }
            }

            else
            {
                for (int i = 0; i < 3; i++)
                {
                    angle_kp[i] = indexes[i] * sortedValues[i] * 22.5 / (sortedValues[0] + sortedValues[1] + sortedValues[2]); // 22.5 is the angle between each sensor
                }
                angle = angle_kp[0] + angle_kp[1] + angle_kp[2];
                lastangle = angle;
                // Serial.println("ree");
            } // end of else statement for normal angle calculation
            loopcounter = 0;
        } // end of if statement if first 3 IRs = 0

    } // end of loopcounter <1

    else if (loopcounter >= 1)
    {
        if (sortedValues[0] > 0)
        {
            angle = 0;
            loopcounter = 0;
        }
        else
        {
            angle = 400; // no ball detected
            lastangle = angle;
            // Serial.println("no ball");
        }
        loopcounter = 0;
    }
    else
        ;

    // Serial.println(loopcounter); //HELP ME
}

uint16_t IRgetAngle()
{
    return angle;
}

float IRgetStrength()
{
    // return strength;
    return strength;
}

// IR timer stuff
Timer::Timer(unsigned long duration)
{
    timerDuration = duration;
}

void Timer::update()
{
    lastUpdate = micros();
}

bool Timer::timeHasPassed()
{
    if (micros() - lastUpdate > timerDuration)
    {
        lastUpdate = micros();
        return true;
    }

    return false;
}

bool Timer::timeHasPassedNoUpdate()
{
    return micros() - lastUpdate > timerDuration;
}

void Timer::resetTime()
{
    lastUpdate = micros();
}

void processballstrength()
{
    if (noValsCounter > 2)
        ballstatus = 1; // if far away return 1
    else
        ballstatus = 0;
}
