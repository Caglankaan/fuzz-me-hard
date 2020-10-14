#pragma once

#ifndef FUZZ_ME_HARD_HEADERS_TIMER
#define FUZZ_ME_HARD_HEADERS_TIMER

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <thread>

class Timer {
    bool clear = false;
    std::mutex mtx; 
    public:
        int elapsed_time{15};
        int time_out_counter{0};
        
        void startTimer(int timeout);
        void addSecond(int interval);

};

void Timer::startTimer(int timeout)
{
    std::thread([&]
    {
        for(;;)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            time_out_counter += 1;

            std::cout << "timeout counter: " << time_out_counter << " (stops when " << timeout << ")\n";
            if(time_out_counter == timeout)
            {
                std::cout << "timeout reached!\n";
                exit(0);
            }
        }
    });
}

void Timer::addSecond(int interval)
{
    this->time_out_counter -= interval;
}

#endif