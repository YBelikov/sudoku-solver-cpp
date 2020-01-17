#pragma once
#include "Solver.h"
using std::vector;

class BackTrackingSolver : public Solver {

    void solve(std::vector<std::vector<int>>& field) override;
};
