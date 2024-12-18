#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day4 final : public DaySolver {
    public:
        Day4();
        ~Day4() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
