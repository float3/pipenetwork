#include "Tube.hpp"
#include "linalg.hpp"
#include <cmath>

namespace cie {
namespace pipenetwork {

Tube::Tube(Node *node1, Node *node2, double diameter)
    : node1_(node1), node2_(node2), diameter_(diameter) {}

double Tube::length() const {
    double dx = node1_->x() - node2_->x();
    double dy = node1_->y() - node2_->y();

    return std::sqrt(dx * dx + dy * dy);
}

double Tube::permeability() const {
    const double pi = 3.1415926535897932384626433832;
    const double g = 9.81;
    const double nu = 1e-6;
    double length = this->length();
    double B_i = (pi * g * std::pow(diameter_, 4)) / (128 * nu * length);
    return B_i;
}

const Node *Tube::node1() const { return node1_; }

const Node *Tube::node2() const { return node2_; }

} // namespace pipenetwork
} // namespace cie
