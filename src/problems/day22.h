#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day22 final : public DaySolver {
    public:
        Day22();
        ~Day22() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
