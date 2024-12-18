#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day13 final : public DaySolver {
    public:

        Day13();
        ~Day13() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
