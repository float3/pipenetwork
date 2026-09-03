#include "PipeNetwork.hpp"
#include "catch.hpp"
#include <fstream>
#include <iostream>

TEST_CASE("Pipenetwork") {
    cie::pipenetwork::PipeNetwork network("input.txt");
    std::vector<double> flux = network.computeFluxes();
    std::ofstream outFile("pipedata.txt");

    for (size_t i = 0; i < flux.size(); ++i) {
        std::cout << "Flux " << i << ": " << flux[i] << " " << std::endl;
        if (outFile.is_open()) {
            outFile << flux[i] << " ";
        }
    }
    std::cout << std::endl;
    outFile.close();
}