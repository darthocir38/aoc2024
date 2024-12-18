#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day7 final : public DaySolver {
    public:
        Day7();
        ~Day7() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
