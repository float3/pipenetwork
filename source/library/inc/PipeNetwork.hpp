#pragma once
#include "Node.hpp"
#include "Tube.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace cie {
namespace pipenetwork {

class PipeNetwork {
  public:
    PipeNetwork(const std::string &filename);

    std::vector<double> computeFluxes() const;

  private:
    std::vector<Node> nodes_;
    std::vector<Tube> tubes_;
};

} // namespace pipenetwork
} // namespace cie
