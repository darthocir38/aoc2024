#pragma once

#include "inputs.h"
#include <chrono>
#include <iostream>
#include <string_view>

namespace adventofcode
{

enum class Part { Part1, Part2 };
using ResultType = std::variant<long, size_t, std::string>;

struct DayResult
{
    ResultType result;
    long duration = 0;
};

class DaySolver
{
public:
    DaySolver() = delete;
    explicit DaySolver(int inDay) : input_data(inputs[inDay - 1]) {}
    virtual ~DaySolver() = default;

    virtual ResultType solvePart1() = 0;
    virtual ResultType solvePart2() = 0;

    DayResult timed_solve(Part part) {
        const auto start = std::chrono::high_resolution_clock::now();
        const auto result = part == Part::Part1 ? solvePart1() : solvePart2();
        const auto end = std::chrono::high_resolution_clock::now();
        return { result, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
    }

    void setup_test() { input_data = test_data; }

    [[nodiscard]] ResultType get_test_result(Part part) const { return test_results[static_cast<size_t>(part)]; }

protected:
    std::string_view input_data;

    std::string test_data;
    std::array<ResultType, 2> test_results {};
};
} // namespace adventofcode

