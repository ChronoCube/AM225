#pragma once
#include <chrono>

class Timer {
  public:
    Timer() : tp{std::chrono::high_resolution_clock::now()} {}

    void tick() { tp = std::chrono::high_resolution_clock::now(); }

    // returns the time (in milliseconds) since the last tick
    // or the construction of the timer
    double elapsed() {
        return std::chrono::duration<double, std::milli>(
                   std::chrono::high_resolution_clock::now() - tp)
            .count();
    }

  private:
    std::chrono::high_resolution_clock::time_point tp;
};
