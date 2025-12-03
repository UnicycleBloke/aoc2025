#include "utils.h"


// template <typename T>
// auto part1(const T& input)
// {
//     aoc::timer timer;
//     int result = 0;

//     for (const auto& bank: input)
//     {
//         int jolt_max = 0;
//         auto size = bank.size();
//         for (auto i = 0U; i < size; ++i)
//         {
//             int jolt_i = (bank[i] - '0') * 10;
//             for (auto j = i + 1; j < size; ++j)
//             {
//                 int jolt_j = bank[j] - '0';
//                 int jolt   = jolt_i + jolt_j;
//                 if (jolt > jolt_max) jolt_max = jolt;                
//             }
//         }

//         result += jolt_max;
//     }

//     return result;
// }


// Find the (first) highest value battery in the bank starting from 'start' and leaving 
// at least 'extra' for the remaining smaller digits in our 12-digit result.
uint64_t find_next(uint64_t input, size_t start, size_t extra, const std::string& bank)
{
    if (extra == 0) return input;

    uint64_t jolt_max = 0;

    auto size   = bank.size();
    auto start2 = start;
    for (auto i = start; i < (size - extra + 1); ++i)
    {       
        uint64_t jolt = bank[i] - '0';
        if (jolt > jolt_max) 
        {
            // Highest value battery since 'start'            
            jolt_max = jolt;
            // The next call to find_next starts after this battery.               
            start2   = i + 1;
        } 
    }

    return find_next(input * 10U + jolt_max, start2, extra - 1, bank);
}


// Re-implementation in terms of Part 2 solution.
template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;
    uint64_t result = 0U;

    for (const auto& bank: input)
    {
        auto jolt = find_next(0U, 0U, 2U, bank);
        result += jolt;
    }

    return result;
}


template <typename T>
auto part2(const T& input)
{
    aoc::timer timer;
    uint64_t result = 0U;

    for (const auto& bank: input)
    {
        auto jolt = find_next(0U, 0U, 12U, bank);
        result += jolt;
    }

    return result;
}


void run(const char* filename)
{
    auto lines = aoc::read_lines(filename);

    auto p1 = part1(lines);
    cout << "Part1: " << p1 << '\n';

    auto p2 = part2(lines);
    cout << "Part2: " << p2 << '\n';
}


int main(int argc, char** argv)
{
    aoc::timer timer;
    try
    {
        if (argc < 2)
        {
            cout << "Provide input file name\n";
            return -1;
        }

        fs::path path{argv[1]};
        if (!fs::is_regular_file(path))
        {
            cout << "Path '" << argv[1] << "' does not exist or is not a file\n";
            return -1;
        }

        run(argv[1]);
    }
    catch (std::exception& e)
    {
        cout << e.what();
    }
}
