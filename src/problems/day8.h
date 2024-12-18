#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day8 final : public DaySolver {
    public:
        Day8();
        ~Day8() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
