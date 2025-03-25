#ifndef POSITION_HPP_INCLUDE
#define POSITION_HPP_INCLUDE

#pragma once

#include <iostream>

struct vectorR2
{
    float x,y;

    vectorR2()
    :x(0.0f), y(0.0f)
    {}

    vectorR2(float p_x, float p_y)
    :x(p_x), y(p_y) 
    {}

};


#endif