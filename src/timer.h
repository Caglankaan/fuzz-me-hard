#pragma once

#ifndef FUZZ_ME_HARD_HEADERS_TIMER
#define FUZZ_ME_HARD_HEADERS_TIMER

#include <iostream>
#include <thread>
#include <chrono>

class Timer {
    public:
        int time_out_reached{0};
        int time_out_counter{0};
        
        void startTimer(int timeout);
        void restart();
        void stop();
};

#endif