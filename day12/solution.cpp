#include "utils.h"


using Item   = array<array<char, 3>, 3>;


template <typename T, typename U>
auto part1(const T& boxes, const U& items)
{
    aoc::timer timer;
    int result = 0;

    // Much time wasted trying to brute force a jigsaw with a massively combinatorial 
    // explosion of potential layouts. So then I run a naive test to see how many 
    // rectangles are definitely too small. And that's it. That's the answer. The whole 
    // thing, including the sample input, was a massively distraction and a waste of time. 
    // Code deleted.
    //
    // I suppose the take away lesson that it is wise to do cheap and simple tests to 
    // eliminate assumptions, before blowing your entire budget for nothing. Fuck you, Eric!
    for (auto [x, y, a, b, c, d, e, f] : boxes)
    {
        size_t area1 = x * y;
        size_t area2 = 9U * (a + b + c + d + e + f);

        result += (area1 >= area2);        
    }

    return result;
}


template <typename T>
auto part2(T &input)
{
    aoc::timer timer;
    int result = 0;

    return result;
}


void run(const char *filename)
{
    auto lines = aoc::read_lines(filename);
    vector<Item> items;
    for (auto i : aoc::range(6))
    {
        auto j = 4 * i + 1;

        Item item;
        for (auto k : aoc::range(3))
        {
            item[k][0] = lines[k+j][0];
            item[k][1] = lines[k+j][1];
            item[k][2] = lines[k+j][2];
        }
        items.push_back(item);
    }

    auto boxes = aoc::read_lines<size_t, size_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>(filename, 
        R"((\d+)x(\d+): (\d+) (\d+) (\d+) (\d+) (\d+) (\d+))");

    auto p1 = part1(boxes, items);
    cout << "Part1: " << p1 << '\n';
}


int main(int argc, char **argv)
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
    catch (std::exception &e)
    {
        cout << e.what();
    }
}
