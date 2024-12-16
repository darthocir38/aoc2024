#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day16 final : public DaySolver {
    public:
        Day16();
        ~Day16() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
