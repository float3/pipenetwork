#include "PipeNetwork.hpp"
#include "linalg.hpp"

namespace cie {
namespace pipenetwork {

PipeNetwork::PipeNetwork(const std::string &filename) {

    std::ifstream infile(filename);

    if (infile.fail()) {
        printf("file does not exist\n");
    }

    int numNodes, numTubes;

    infile >> numNodes >> numTubes;

    nodes_.reserve(numNodes);
    tubes_.reserve(numTubes);

    for (int i = 0; i < numNodes; ++i) {
        double x, y, flow;
        int id = i;
        infile >> x >> y >> flow;

        nodes_.emplace_back(x, y, flow, id);
    }

    for (int i = 0; i < numTubes; ++i) {
        int startNodeId, endNodeId;
        double diameter;
        infile >> startNodeId >> endNodeId >> diameter;
        Node *startNode = &nodes_[startNodeId];
        Node *endNode = &nodes_[endNodeId];

        tubes_.emplace_back(startNode, endNode, diameter);
    }
}

std::vector<double> PipeNetwork::computeFluxes() const {

    int numNodes = nodes_.size();
    int numTubes = tubes_.size();

    linalg::Matrix B(numNodes, numNodes, 0.0);

    for (int i = 0; i < numTubes; ++i) {
        int id1 = tubes_[i].node1()->id();
        int id2 = tubes_[i].node2()->id();
        double B_i = tubes_[i].permeability();

        B(id1, id1) += B_i;
        B(id2, id2) += B_i;
        B(id1, id2) -= B_i;
        B(id2, id1) -= B_i;
    }
    std::vector<double> Q(numNodes, 0.0);

    for (int i = 1; i < numNodes; ++i) {
        Q[i] = -(nodes_[i].flow());
        B(i, 0) = 0;
        B(0, i) = 0;
    }

    B(0, 0) = 1;
    Q[0] = 0;

    std::vector<double> head = cie::linalg::solve(B, Q);
    std::vector<double> q(numTubes);
    for (int i = 0; i < numTubes; ++i) {
        int id1 = tubes_[i].node1()->id();
        int id2 = tubes_[i].node2()->id();

        q[i] = tubes_[i].permeability() * (head[id1] - head[id2]);
    }
    return q;
}

} // namespace pipenetwork
} // namespace cie