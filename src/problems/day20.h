#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day20 final : public DaySolver {
    public:
        Day20();
        ~Day20() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
