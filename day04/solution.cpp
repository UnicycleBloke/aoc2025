#include "utils.h"


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;
    int result = 0;

    int rows = input.size();
    int cols = input[0].size();

    auto rolls = [&](auto r, auto c)
    {
        int count = 0;
        count += input[r + 1][c + 1] == '@';
        count += input[r + 1][c]     == '@';
        count += input[r + 1][c - 1] == '@';

        count += input[r][c + 1] == '@';
        //count += input[r][c]     == '@';
        count += input[r][c - 1] == '@';

        count += input[r - 1][c + 1] == '@';
        count += input[r - 1][c]     == '@';
        count += input[r - 1][c - 1] == '@';

        return count;  
    };

    for (auto r: aoc::range(1, rows - 1))
    {
        for (auto c: aoc::range(1, cols - 1))
        {
            if (input[r][c] == '@')
            {
                result += rolls(r, c) < 4;        
            }
        }
    }

    return result;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    int result = 0;

    int rows = input.size();
    int cols = input[0].size();

    auto rolls = [&](auto r, auto c)
    {
        int count = 0;
        count += input[r + 1][c + 1] == '@';
        count += input[r + 1][c]     == '@';
        count += input[r + 1][c - 1] == '@';

        count += input[r][c + 1] == '@';
        //count += input[r][c]     == '@';
        count += input[r][c - 1] == '@';

        count += input[r - 1][c + 1] == '@';
        count += input[r - 1][c]     == '@';
        count += input[r - 1][c - 1] == '@';

        return count;  
    };

    // This code removes each roll immediately rather than marking with x and then removing all 
    // the the marked rolls (could use two grids for this like a cellular automaton). I thought 
    // it was a bug because the number removed per cycles differed from the example. But the 
    // total removed was the same. Interesting.  
    int removed = 1;
    while (removed > 0)
    {
        removed = 0;
        for (auto r: aoc::range(1, rows - 1))
        {
            for (auto c: aoc::range(1, cols - 1))
            {
                if (input[r][c] == '@')
                {
                    removed += rolls(r, c) < 4;        
                    if (rolls(r, c) < 4) input[r][c] = '.';
                }
            }
        }

        result += removed;
    }

    return result;
}


void run(const char* filename)
{
    auto lines = aoc::read_grid_with_border(filename, 1, '.');

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
