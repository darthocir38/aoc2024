#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day18 final : public DaySolver {
    public:
        Day18();
        ~Day18() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}