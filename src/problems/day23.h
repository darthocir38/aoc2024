#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day23 final : public DaySolver {
    public:
        Day23();
        ~Day23() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
