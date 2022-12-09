#include "Stopwatch.h"

std::shared_ptr<Stopwatch> Stopwatch::stopwatch(new Stopwatch);

std::shared_ptr<Stopwatch> Stopwatch::getInstance() { return stopwatch; }

double Stopwatch::timeSinceLastUpdate() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - lastUpdate).count() /
           1e9;
}

void Stopwatch::reset() { lastUpdate = std::chrono::steady_clock::now(); }
