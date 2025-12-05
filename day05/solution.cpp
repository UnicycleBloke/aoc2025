#include "utils.h"


template <typename T, typename U>
auto part1(const T& ranges, const U& stocks)
{
    aoc::timer timer;
    int result = 0;

    for (auto [s]: stocks)
    {
        for (auto [b, e]: ranges)
        {
            if ((s >= b) && (s <= e)) 
            {
                ++result;
                break;
            }
        }
    }

    return result;
}


template <typename T>
auto part2(T& ranges)
{
    aoc::timer timer;
    uint64_t result = 0;

    // Tuples conventiently sort in just the way we need. We want 
    // to the order the ranges by start value and then by end value.
    sort(ranges.begin(), ranges.end());

    uint64_t beg = 0;
    uint64_t end = 0;

    // Deal with overlapping ranges by extending the end value of a 
    // combined range until the start value of a range falls after the
    // end of the combined ranges. Then add the size of the combined range
    // to the total and start a fresh one.  
    for (auto [b, e]: ranges)
    {
        if (b > end)
        {
            result += (end - beg) + 1;
            beg = b;
            end = e;
        }
        else if (e > end)
        {
            end = e;
        }
    }
    result += (end - beg) + 1;

    // Account for the extra value due to the initial null range. Should 
    // probably account for empty ranges better in general, but this seems 
    // sufficient for the problem.
    return result - 1;
}


void run(const char* filename)
{
    //template <class... Args>
    //std::vector<std::tuple<Args...>> read_lines(std::string filename, std::string pat, const std::string& delim = ";")
    auto ranges = aoc::read_lines<uint64_t, uint64_t>(filename, R"((\d+)-(\d+))");
    auto stocks = aoc::read_lines<uint64_t>(filename, R"((\d+))");

    auto p1 = part1(ranges, stocks);
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
