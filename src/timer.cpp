#include "timer.h"

void Timer::startTimer(int timeout)
{
    if(timeout == -1)
        return;
    this->time_out_reached = timeout;
    std::thread([&]
    {
        for(;;)
        {
            if(time_out_counter == this->time_out_reached)
            {
                std::cout << "timeout reached!(" << this->time_out_reached << " second!)\n";
                exit(0);
            }
            else if(time_out_counter == -1)
            {
                std::cout << "already breaked\n";
                break;
            }
            time_out_counter += 1;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}

void Timer::restart()
{
    this->time_out_counter = 0;
}

void Timer::stop()
{
    this->time_out_counter = -1;
}