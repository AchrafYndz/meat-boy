#include "Stopwatch.h"

std::shared_ptr<Utility::Stopwatch> Utility::Stopwatch::stopwatch(new Stopwatch);

double Utility::Stopwatch::timeSinceLastUpdate() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - lastUpdate).count() /
           1e9;
}

void Utility::Stopwatch::reset() { lastUpdate = std::chrono::steady_clock::now(); }
