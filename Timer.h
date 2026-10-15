#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Stopwatch for measuring program operating time
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    void reset() { start = std::chrono::high_resolution_clock::now(); }
    // Seconds since construction / last reset
    double elapsed() const {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    }
};

#endif
