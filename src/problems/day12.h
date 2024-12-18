#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day12 final : public DaySolver {
    public:
        Day12();
        ~Day12() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
