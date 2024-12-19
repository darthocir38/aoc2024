#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day19 final : public DaySolver {
    public:
        Day19();
        ~Day19() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
