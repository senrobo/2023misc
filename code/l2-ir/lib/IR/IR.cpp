#include <IR.h>

void IR::initIR()
{
    pinMode(17, INPUT);
    pinMode(16, INPUT);
    pinMode(15, INPUT);
    pinMode(14, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
    pinMode(46, INPUT);
    pinMode(45, INPUT);
    pinMode(43, INPUT);
    pinMode(42, INPUT);
    pinMode(41, INPUT);
    pinMode(40, INPUT);
    pinMode(39, INPUT);
    pinMode(38, INPUT);
    pinMode(29, INPUT);
    pinMode(28, INPUT);
    pinMode(27, INPUT);
    pinMode(26, INPUT);
    pinMode(25, INPUT);
    pinMode(22, INPUT);
    pinMode(21, INPUT);
    pinMode(20, INPUT);
    pinMode(19, INPUT);
    pinMode(18, INPUT);
}

void IR::readIR(int n)
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

void IR::processIR()
{
    // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
    for (uint8_t i = 0; i < IR_NUM; i++)
    {
        values[i] = 100 * (double)tempValues[i] / (double)IRCounter; // multiply each value in the array by 100 then divide it by number of times it read the sensors
        tempValues[i] = 0;                                           // reset values here
        sortedValues[i] = 0;
        indexes[i] = 0;
    }

    IRCounter = 0;

    IRsortvalues();
    IRcalculateanglestrength(BEST_IR_NUMBER);
}

void IR::IRsortvalues()
{
    // Sort the TSOP values from greatest to least in sortedFilteredValues
    // and sort the TSOP indexes from greatest to least strength in indexes (array positions)

    for (uint8_t i = 0; i < IR_NUM; i++)
    {
        for (uint8_t j = 0; j < IR_NUM; j++)
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

void IR::IRcalculateanglestrength(int n)
{
    // Cartesian addition of best n TSOPs
    float s = 0;
    float t = 0;
    noValsCounter = 0;

    for (int i = 0; i < 16; i++)
    {
        s += sortedValues[i]; // addition of all values in the array and sum up as 's'
    }
    for (int i = 0; i < n; i++)
    {
        t += sortedValues[i];
    }
    for (int i = 0; i < 16; i++)
    {
        if (sortedValues[i] == 0)
            noValsCounter++;
    }
    strength = t / s; // calculate strength as a proportion number, between 0 and 1 ***check reliability, didnt end up using it anyways lmao
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
                    angle_kp[i] = indexes[i] * sortedValues[i] * 22.5 / (sortedValues[0] + sortedValues[1] + sortedValues[2]);
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