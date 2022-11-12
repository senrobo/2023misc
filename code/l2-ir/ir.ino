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

    tsopCounter++; //+1 to counter to count the no. of times it read
}
}