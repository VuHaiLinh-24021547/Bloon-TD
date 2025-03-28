#ifndef TIMER_HPP_INCLUDE
#define TIMER_HPP_INCLUDE

#pragma once

class timer
{
    public:
        timer(int p_max_time);
        void time_passed();
        void get_time_to_max();
        bool time_is_zero();
    private:
        int current_time;
        int max_time;
        int spawn_count;
};

#endif