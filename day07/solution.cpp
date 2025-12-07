#include "utils.h"


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;

    // Use a set for the beams to avoid duplicates after splits.
    set<uint32_t> beams;
    uint32_t      splits = 0;

    // Find the initial beam location.
    const auto& row = input[0]; 
    for (auto b: aoc::range(row.size()))
    {
        if (row[b] == 'S')
        {
            beams.insert(b);
            break;
        }
    }

    // For each beam either propogate or split, creating a revised set of beams.
    for (auto r: aoc::range(1U, input.size()))
    {
        const auto& row = input[r]; 

        set<uint32_t> beams2;
        for (auto b: beams)
        {
            if (row[b] == '^')
            {
                // Split the beam.
                beams2.insert(b - 1);
                beams2.insert(b + 1);
                ++splits;
            }
            else
            {
                beams2.insert(b);
            }
        }


        beams = beams2; 
    }

    return splits;
}


template <typename T>
auto part2(const T& input)
{
    aoc::timer timer;
    
    // Almost identical logic to Part1 but use a map instead of a set to keep track of the 
    // numbers of timelines in each column. Sum these at the end for the result.
    map<uint32_t, uint64_t> beams;

    // Find the initial beam location.
    const auto& row = input[0]; 
    for (auto b: aoc::range(row.size()))
    {
        if (row[b] == 'S')
        {
            beams[b] = 1;
            break;
        }
    }

    // For each beam either propogate or split, creating a revised set of beams.
    for (auto r: aoc::range(1U, input.size()))
    {
        const auto& row = input[r]; 

        map<uint32_t, uint64_t> beams2;
        for (auto [b, lines]: beams)
        {
            if (row[b] == '^')
            {
                // Split the beam.
                beams2[b - 1] = beams2[b - 1] + lines;
                beams2[b + 1] = beams2[b + 1] + lines;
            }
            else
            {
                beams2[b] = beams2[b] + lines;
            }
        }


        beams = beams2; 
    }

    uint64_t result = 0;
    for (auto [b, lines]: beams)
    {
        result += lines;
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
