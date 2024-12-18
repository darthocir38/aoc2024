#include "day17.h"
#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"

#include <math.h>
#include <print>
#include <valarray>

namespace adventofcode
{
Day17::Day17() : DaySolver(17) {
    // Data for tests
    test_data = R"(Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0)";
    test_results = { 0, 0 };
}

struct CPU
{
    CPU(auto const& content) {
        for (const auto& l : content) {
            auto v = split(l, ':');
            if (v[0] == "Register A") {
                a = std::stoul(v[1]);
                continue;
            }
            if (v[0] == "Register B") {
                b = std::stoul(v[1]);
                continue;
            }
            if (v[0] == "Register C") {
                c = std::stoul(v[1]);
                continue;
            }
            if (v[0] == "Program") {
                program = convert<uint>(split(v[1].substr(1), ','));
            }
        }
    }

    uint64_t get_operand(uint val) {
        if (val >= 0 && val <= 3) {
            return val;
        }
        if (val == 4) {
            return a;
        }
        if (val == 5) {
            return b;
        }
        if (val == 6) {
            return c;
        }

        std::println("error found operaand:  {}", val);
        exit(1);
    }

    uint64_t div(uint64_t x, uint64_t y) {

        uint64_t bla = (1L << y) & (long)0xFFFFFFFF;

        return x / bla;
    }

    void step() {
        // std::println("ptr: {}, opcode: {}, operand: {}, op-value-dec: ", instr_ptr, program.at(instr_ptr),
        // program.at(instr_ptr + 1));
        switch (program[instr_ptr]) {
        case 0:
            // adv div
            a = div(a, get_operand(program[instr_ptr + 1]));
            break;
        case 1:
            // bxl xor
            {
                auto op = program[instr_ptr + 1];
                auto res = b ^ op;
                b = res;
            }
            break;
        case 2:
            // combo mod 8
            b = get_operand(program[instr_ptr + 1]) % 8;
            break;
        case 3:
            // jump
            if (a != 0)
                instr_ptr = program[instr_ptr + 1] - 2;
            break;
        case 4:
            // bxc
            b = b ^ c;
            break;
        case 5:
            // out
            // std::print("{},", get_operand(program[instr_ptr + 1]) % 8);
            output.push_back(get_operand(program[instr_ptr + 1]) % 8);
            break;
        case 6:
            // bdv div
            b = div(a, get_operand(program[instr_ptr + 1]));
            break;
        case 7:
            // bdv div
            c = div(a, get_operand(program[instr_ptr + 1]));
            break;
        default:
            std::print("invalid opcode: {}", program[instr_ptr]);
            exit(1);
        }

        instr_ptr += 2;
        running = instr_ptr < program.size();
    }

    void reverse() { instr_ptr -= 2; }

    bool running = true;

    uint64_t a, b, c;
    std::vector<uint> program;
    uint instr_ptr = 0;
    std::vector<uint> output;
};

ResultType Day17::solvePart1() {
    const auto content = split(input_data, '\n');
    CPU cpu(content);

    while (cpu.running) {
        cpu.step();
    }

    return to_str(cpu.output);
}

bool cmpVectors(std::vector<uint> a, std::vector<uint> b) {
    int offset = b.size() - a.size();
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i + offset])
            return false;
    }

    return true;
}

ResultType Day17::solvePart2() {
    const auto content = split(input_data, '\n');
    CPU cpu(content);

    uint64_t my_a = 0;
    bool cont = true;
    do {
        auto cpu2 = cpu;
        cpu2.a = my_a;
        while (cpu2.running) {
            cpu2.step();
        }

        if (cpu2.output == cpu.program) {
            cont = false;
        } else {
            if (cmpVectors(cpu2.output, cpu.program)) {
                my_a = my_a * 8;
            } else {
                my_a++;
            }
        }
    } while (cont);

    return my_a;
}

} // namespace adventofcode
