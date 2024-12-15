#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day13 final : public DaySolver {
    public:

        Day13();
        ~Day13() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
