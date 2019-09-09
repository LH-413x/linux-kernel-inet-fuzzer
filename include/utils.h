//
// Created by liuhao on 2019/9/9.
//

#ifndef ROUTE_UTILS_H
#define ROUTE_UTILS_H

//#include <iostream>
#include <random>

int getRand();
int getRand(uint32_t max, uint32_t min);

#define ELEM_NUM(a) sizeof((a))/sizeof((a)[0])
#define RAND_FROM(x) (x)[getRand()%ELEM_NUM((x))]


#endif //ROUTE_UTILS_H
