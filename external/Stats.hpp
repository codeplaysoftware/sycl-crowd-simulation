#ifdef STATS
#include "Actor.hpp"
#include "VectorMaths.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sycl/sycl.hpp>

void updateStats(sycl::queue myQueue, sycl::buffer<Actor> actorBuf,
                 std::vector<float> &averageForces,
                 std::vector<int> &destinationTimes,
                 std::chrono::high_resolution_clock::time_point startPoint);

void finalizeStats(sycl::queue myQueue, std::vector<float> averageForces,
                   std::vector<int> destinationTimes,
                   std::vector<int> kernelDurations, int numActors,
                   int totalExecutionTime);
#endif
