#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day21 final : public DaySolver {
    public:
        Day21();
        ~Day21() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
