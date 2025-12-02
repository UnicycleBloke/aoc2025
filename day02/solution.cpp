#include "utils.h"


auto num_digits(uint64_t i)
{
    uint16_t n = 0;
    while (i > 0)
    {
        ++n;
        i = i / 10;
    }
    return n;
};


template <typename T>
auto part1(const T& ranges)
{
    aoc::timer timer;
    uint64_t result = 0;

    for (auto [from, to]: ranges)
    {
        for (auto id: aoc::range(from, to + 1))
        {
            auto digits = num_digits(id);
            if (digits % 2) continue;
            digits = digits / 2;

            uint64_t scale = 1;
            for (uint16_t i = 0; i < digits; ++i)
                scale *= 10; 
                
            uint64_t lower = id % scale;    
            uint64_t upper = id / scale;
            uint64_t id2   = lower * scale + upper;
            if (id2 == id)
                result += id;
        }
    }

    return result;
}


template <typename T>
auto part2(const T& ranges)
{
    aoc::timer timer;
    uint64_t result = 0;

    for (auto [from, to]: ranges)
    {
        for (auto id: aoc::range(from, to + 1))
        {
            auto digits = num_digits(id);
            for (uint16_t digits2 = 1; digits2 <= digits / 2; ++digits2)
            {
                if (digits % digits2) continue;

                uint64_t scale = 1;
                for (uint16_t i = 0; i < digits2; ++i)
                    scale *= 10;
                    
                uint64_t id2     = id;
                uint64_t part    = id % scale;
                bool     invalid = true;
                while (id2 > 0)
                {
                    invalid &= ((id2 % scale) == part);
                    id2 = id2 / scale;
                }                      

                if (invalid)
                {
                    result += id;
                    // Avoid double counting
                    break;
                }
            }
        }
    }

    return result;
}


void run(const char* filename)
{
    auto lines = aoc::read_lines(filename);
    auto split = aoc::split(lines[0], ",");

    struct Range 
    {
        uint64_t from;
        uint64_t to;
    };

    vector<Range> ranges; 
    for (auto s: split)
    {
        istringstream is{s};
        Range r;
        is >> r.from;
        is.ignore();
        is >> r.to;
        ranges.push_back(r);
    }

    auto p1 = part1(ranges);
    cout << "Part1: " << p1 << '\n';

    auto p2 = part2(ranges);
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
