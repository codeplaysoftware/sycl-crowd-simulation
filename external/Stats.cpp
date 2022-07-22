#ifdef STATS
#include "Stats.hpp"

void updateStats(sycl::queue myQueue, sycl::buffer<Actor> actorBuf,
                 std::vector<float> &averageForces,
                 std::vector<int> &destinationTimes,
                 std::chrono::high_resolution_clock::time_point startPoint) {
    try {
        float forceSum = 0;
        auto forceSumBuf = sycl::buffer<float>(&forceSum, 1);

        // Calculate average force applied to actors this iteration
        myQueue
            .submit([&](sycl::handler &cgh) {
                auto actorAcc =
                    actorBuf.get_access<sycl::access::mode::read>(cgh);

                auto sumReduction =
                    sycl::reduction(forceSumBuf, cgh, sycl::plus<float>());

                cgh.parallel_for(sycl::range<1>{actorAcc.size()}, sumReduction,
                                 [=](sycl::id<1> index, auto &sum) {
                                     sum += actorAcc[index].getPrevForce();
                                 });
            })
            .wait_and_throw();

        sycl::host_accessor<float, 1, sycl::access::mode::read> forceSumHostAcc(
            forceSumBuf);
        averageForces.push_back(forceSumHostAcc[0] / actorBuf.size());

        // Find actors which have reached their destination and record how long
        // it took them
        auto destinationTimesBuf =
            sycl::buffer<int>(destinationTimes.data(), destinationTimes.size());

        myQueue
            .submit([&](sycl::handler &cgh) {
                auto actorAcc =
                    actorBuf.get_access<sycl::access::mode::read>(cgh);
                auto destinationTimesAcc =
                    destinationTimesBuf
                        .get_access<sycl::access::mode::read_write>(cgh);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        end - startPoint)
                        .count();

                cgh.parallel_for(sycl::range<1>{destinationTimesAcc.size()},
                                 [=](sycl::id<1> index) {
                                     if (actorAcc[index].getAtDestination() &&
                                         destinationTimesAcc[index] == 0) {
                                         destinationTimesAcc[index] = duration;
                                     }
                                 });
            })
            .wait_and_throw();

        sycl::host_accessor<int, 1, sycl::access::mode::read>
            destinationTimesHostAcc(destinationTimesBuf);
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n"
                  << e.what() << "\n[updateStats]";
    }
}

void finalizeStats(sycl::queue myQueue, std::vector<float> averageForces,
                   std::vector<int> destinationTimes,
                   std::vector<int> kernelDurations, int numActors,
                   int totalExecutionTime) {
    try {
        int durationSum = 0;
        auto durationSumBuf = sycl::buffer<int>(&durationSum, 1);

        auto kernelDurationsForOutput = kernelDurations;
        kernelDurations.erase(kernelDurations.begin());
        auto kernelDurationsBuf =
            sycl::buffer<int>(kernelDurations.data(), kernelDurations.size());

        // Calculate average kernel duration
        myQueue
            .submit([&](sycl::handler &cgh) {
                auto durationAcc =
                    kernelDurationsBuf.get_access<sycl::access::mode::read>(
                        cgh);

                auto sumReduction =
                    sycl::reduction(durationSumBuf, cgh, sycl::plus<int>());

                cgh.parallel_for(sycl::range<1>{durationAcc.size()},
                                 sumReduction,
                                 [=](sycl::id<1> index, auto &sum) {
                                     sum += durationAcc[index];
                                 });
            })
            .wait_and_throw();

        sycl::host_accessor<int, 1, sycl::access::mode::read>
            durationSumHostAcc(durationSumBuf);
        float avgKernelDuration =
            float(durationSumHostAcc[0]) / float(kernelDurations.size());

        // Write results to ../output/outputStats.txt
        std::ofstream outputFile;
        outputFile.open("../output/outputStats.txt", std::ios::out);

        outputFile << "No. of actors: " << numActors << std::endl;
        outputFile << "Average kernel executation time: " << avgKernelDuration
                   << "μs   NOTE: First kernel time has been disregarded"
                   << std::endl;
        outputFile << "Total execution time: " << totalExecutionTime << "μs"
                   << std::endl;
        outputFile << std::endl << std::endl;

        outputFile << "Actor ID | Time to Reach Destination (ms)" << std::endl;
        outputFile << "-----------------------------------------" << std::endl;
        for (int x = 0; x < destinationTimes.size(); x++) {
            outputFile << std::setprecision(2) << std::fixed;
            outputFile << std::setw(8) << x << " |";
            if (destinationTimes[x] == 0) {
                outputFile << std::setw(30) << "NA";
            } else {
                outputFile << std::setw(30) << destinationTimes[x];
            }
            outputFile << std::endl;
        }
        outputFile << std::endl << std::endl;

        outputFile << "Timestep | Average Force (N)" << std::endl;
        outputFile << "----------------------------" << std::endl;
        for (int x = 0; x < averageForces.size(); x++) {
            outputFile << std::setprecision(2) << std::fixed;
            outputFile << std::setw(8) << x * 100 << " |";
            outputFile << std::setw(17) << averageForces[x];
            outputFile << std::endl;
        }
        outputFile << std::endl << std::endl;

        outputFile << "Kernel no. |     Execution Time (μs)" << std::endl;
        outputFile << "------------------------------------" << std::endl;
        for (int x = 0; x < kernelDurationsForOutput.size(); x++) {
            outputFile << std::setprecision(2) << std::fixed;
            outputFile << std::setw(10) << x << " |";
            outputFile << std::setw(23) << kernelDurationsForOutput[x];
            outputFile << std::endl;
        }

        outputFile.close();

        std::cout << "Stats have been written to ../output/outputStats.txt"
                  << std::endl;
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n"
                  << e.what() << "\n[finalizeStats]";
    }
}
#endif
