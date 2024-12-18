#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day16 final : public DaySolver {
    public:
        Day16();
        ~Day16() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
