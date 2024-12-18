#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day9 final : public DaySolver {
    public:
        Day9();
        ~Day9() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
