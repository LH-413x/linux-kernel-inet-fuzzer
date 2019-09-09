//
// Created by liuhao on 2019/9/9.
//
#include <utils.h>

int getRand(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 0x100);
    return dis(gen);
}

int getRand(uint32_t max, uint32_t min){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}