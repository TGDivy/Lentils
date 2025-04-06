#include <chrono>
#include <iostream>

struct ScopedTimer {
  std::chrono::high_resolution_clock::time_point start;
  std::string_view desc;

  ScopedTimer(std::string_view description)
      : start(std::chrono::high_resolution_clock::now()), desc(description) {}

  ~ScopedTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::format("{} took {} ms\n", desc, duration.count());
  }
};

#define TIMER_MS(desc, code)                                                   \
  do {                                                                         \
    auto start = std::chrono::high_resolution_clock::now();                    \
    code;                                                                      \
    auto end = std::chrono::high_resolution_clock::now();                      \
    auto duration =                                                            \
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);    \
    std::cout << std::format("{} took {} ms\n", desc, duration.count());       \
  } while (0)
