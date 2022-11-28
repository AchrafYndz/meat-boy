#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H

#include <string>
#include <chrono>
#include <memory>

class Stopwatch {
private:
    // constructor must be private
    Stopwatch() = default;

    // the only instance of stopwatch
    static std::unique_ptr<Stopwatch> stopwatch;
    // time of last reset
    std::chrono::time_point<std::chrono::steady_clock> lastUpdate = std::chrono::steady_clock::now();
public:
    // singletons cannot be cloneable.
    Stopwatch(Stopwatch& other) = delete;

    // singletons cannot be assignable
    void operator=(const Stopwatch& other) = delete;

    // returns the only instance of stopwatch
    static Stopwatch* getInstance();

    // the time (in seconds) since reset() was last called
    double timeSinceLastUpdate();

    // resets the time since last update to now
    void reset();
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H
