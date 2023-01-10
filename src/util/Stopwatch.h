#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H

#include <chrono>
#include <memory>
#include <string>

namespace Utility {

/**
 * The Stopwatch class is a singleton class for measuring the time elapsed since last reset. It is used to assure the
 * game runs at a reasonable constant framerate on all machines.
 */
class Stopwatch {
private:
    /**
     * @brief a singleton's constructor must be private
     */
    Stopwatch() = default;

    /** the only instance of stopwatch */
    static std::shared_ptr<Stopwatch> stopwatch;
    /** time of last reset */
    std::chrono::time_point<std::chrono::steady_clock> lastUpdate = std::chrono::steady_clock::now();

public:
    /**
     * @brief singletons cannot be cloneable.
     * */
    Stopwatch(Stopwatch& other) = delete;

    /**
     * @brief singletons cannot be assignable
     */
    void operator=(const Stopwatch& other) = delete;

    /**
     * @brief returns the only instance of stopwatch
     *
     * @return the only instance of stopwatch
     */
    static std::shared_ptr<Stopwatch> getInstance() { return stopwatch; };

    /**
     * returns the time in seconds since reset() was last called
     *
     * @return the time (in seconds) since reset() was last called
     */
    double timeSinceLastUpdate();

    /**
     * resets the time since last update to now
     */
    void reset();
};
} // namespace Utility

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STOPWATCH_H
