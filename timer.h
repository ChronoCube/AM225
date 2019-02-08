#include <chrono>

class Timer {
public:
  Timer() : tp{std::chrono::high_resolution_clock::now()} {}

  void tick() {
    tp = std::chrono::high_resolution_clock::now();
  }

  double elapsed() {
    return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - tp).count();
  }

private:
  std::chrono::high_resolution_clock::time_point tp;
};
