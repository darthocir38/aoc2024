#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day15 final : public DaySolver {
    public:
        Day15();
        ~Day15() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
