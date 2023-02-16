#include <IR.h>

void IR::initIR()
{
    pinMode(IR_ONE, INPUT);
    pinMode(IR_TWO, INPUT);
    pinMode(IR_THREE, INPUT);
    pinMode(IR_FOUR, INPUT);
    pinMode(IR_FIVE, INPUT);
    pinMode(IR_SIX, INPUT);
    pinMode(IR_SEVEN, INPUT);
    pinMode(IR_EIGHT, INPUT);
    pinMode(IR_NINE, INPUT);
    pinMode(IR_TEN, INPUT);
    pinMode(IR_ELEVEN, INPUT);
    pinMode(IR_TWELVE, INPUT);
    pinMode(IR_THIRTEEN, INPUT);
    pinMode(IR_FOURTEEN, INPUT);
    pinMode(IR_FIFTEEN, INPUT);
    pinMode(IR_SIXTEEN, INPUT);
    pinMode(IR_SEVENTEEN, INPUT);
    pinMode(IR_EIGHTEEN, INPUT);
    pinMode(IR_NINETEEN, INPUT);
    pinMode(IR_TWENTY, INPUT);
    pinMode(IR_TWENTYONE, INPUT);
    pinMode(IR_TWENTYTWO, INPUT);
    pinMode(IR_TWENTYTHREE, INPUT);
    pinMode(IR_TWENTYFOUR, INPUT);
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

