#include "timer.hpp"

timer::timer(int p_max_time)
:max_time(p_max_time) {
    current_time = max_time;
}

void timer::time_passed() {
    current_time--;
}

bool timer::time_is_zero() {
    return (current_time <= 0);
}

void timer::get_time_to_max() {
    current_time = max_time;
}