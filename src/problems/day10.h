#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day10 final : public DaySolver {
    public:
        Day10();
        ~Day10() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
