int dist(char WALL[]){
    if (WALL == "LEFT"){
        int irLeft = 0;
        for(int dacVal = 0; dacVal < 160; dacVal += 8 ){
            dac_ctr(26, 0, dacVal);
            freqout(11, 1, 38000);
            irLeft += input(10);
        }
        // printf("%i\n", irLeft);
        return irLeft;
    }else if(WALL =="RIGHT"){
        int irRight = 0;
        for(int dacVal = 0; dacVal < 160; dacVal += 8){
            dac_ctr(27, 1, dacVal);
            freqout(1, 1, 38000);
            irRight += input(2);
        }
        // printf("%i\n", irRight);
        return irRight;
    }
}
