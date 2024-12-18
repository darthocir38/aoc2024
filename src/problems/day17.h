#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day17 final : public DaySolver {
    public:
        Day17();
        ~Day17() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
