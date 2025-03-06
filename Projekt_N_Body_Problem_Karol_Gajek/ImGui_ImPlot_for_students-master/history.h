#pragma once

#include <vector>

class history {
public:
    std::vector<double> x;
    std::vector<double> y;

    history();
    history(std::vector<double> xvec, std::vector<double> yvec);
    void update(double xpoint, double ypoint);
};