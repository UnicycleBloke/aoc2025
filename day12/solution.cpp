#include "utils.h"


using Item   = array<array<char, 3>, 3>;
using Counts = array<int, 6>;
using Grid   = vector<string>;


int g_fitted = 0;


Item rotate(Item item)
{
    Item result{};

    result[0][0] = item[0][2];
    result[0][2] = item[2][2];
    result[2][2] = item[2][0];
    result[2][0] = item[0][0];

    result[0][1] = item[1][2];
    result[1][2] = item[2][1];
    result[2][1] = item[1][0];
    result[1][0] = item[0][1];

    return result;
}


Item flip(Item item)
{
    Item result{};

    result[0][0] = item[0][2];
    result[1][0] = item[1][2];
    result[2][0] = item[2][2];

    result[0][2] = item[0][0];
    result[1][2] = item[1][0];
    result[2][2] = item[2][0];

    return result;
}


bool place_item_impl(Grid& grid, const Item& item, char name)
{
    auto rows = grid.size()    - 2;
    auto cols = grid[0].size() - 2;

    for (auto r: aoc::range(rows))
    {
        for (auto c: aoc::range(rows))
        {
            bool fits = true;
            for (auto k: aoc::range(3))
            {
                fits = fits && (grid[r+k][c]   == '.' || item[k][0] == '.');
                fits = fits && (grid[r+k][c+1] == '.' || item[k][1] == '.');
                fits = fits && (grid[r+k][c+2] == '.' || item[k][2] == '.');
            }

            if (fits)
            {
                // for (auto k : aoc::range(3))
                //     cout << item[k][0] << item[k][1] << item[k][2] << "\n";
                // cout << "\n";

                for (auto k: aoc::range(3))
                {
                    // if (item[k][0] == '#') grid[r+k][c]   = name;
                    // if (item[k][1] == '#') grid[r+k][c+1] = name;
                    // if (item[k][2] == '#') grid[r+k][c+2] = name;
                    if (item[k][0] == '#') grid[r+k][c]   = '#';
                    if (item[k][1] == '#') grid[r+k][c+1] = '#';
                    if (item[k][2] == '#') grid[r+k][c+2] = '#';
                }

                // for (const auto g: grid) 
                //     cout << g << "\n"; 
                // cout << "\n\n";

                return true;
            } 
        }
    }

    return false;
}


bool place_item(Grid& grid, const Item& item, char name)
{
    auto item_r0 = item;
    if (place_item_impl(grid, item_r0, name)) return true;
    
    auto item_r1 = rotate(item_r0);
    if (place_item_impl(grid, item_r1, name)) return true;

    auto item_r2 = rotate(item_r1);
    if (place_item_impl(grid, item_r2, name)) return true;

    auto item_r3 = rotate(item_r2);
    if (place_item_impl(grid, item_r3, name)) return true;

    auto item_f0 = flip(item_r0);
    if (place_item_impl(grid, item_f0, name)) return true;

    auto item_f1 = rotate(item_f0);
    if (place_item_impl(grid, item_f1, name)) return true;

    auto item_f2 = rotate(item_f1);
    if (place_item_impl(grid, item_f2, name)) return true;

    auto item_f3 = rotate(item_f2);
    if (place_item_impl(grid, item_f3, name)) return true;

    return false;
}


void check_grid(const vector<Item>& items, const Counts& target, Counts placed, 
    Grid& grid, bool& fitted, char name)
{
    if (fitted) return;
     
    if (target == placed)
    {
        for (const auto g: grid) 
            cout << g << "\n"; 
        cout << "\n\n";

        fitted = true;
        return;
    }

    for (auto t: aoc::range(6))
    {
        // We have enough of this item
        if (placed[t] >= target[t]) continue;

        Grid grid2 = grid;
        if (place_item(grid2, items[t], name))
        {
            name = name + 1;
            ++placed[t];
            check_grid(items, target, placed, grid2, fitted, name);
            --placed[t];            
            name = name - 1;
        }
    }
}


template <typename T, typename U>
auto part1(const T& boxes, const U& items)
{
    aoc::timer timer;
    int result = 0;

    for (auto [x, y, a, b, c, d, e, f] : boxes)
    {
        array<int, 6> target{a, b, c, d, e, f};
        array<int, 6> placed{};

        string row(x, '.');
        vector<string> grid{y, row};

        bool fitted = false;
        check_grid(items, target, placed, grid, fitted, 'A');
        result += fitted;
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

    auto boxes = aoc::read_lines<size_t, size_t, int, int, int, int, int, int>(filename, R"((\d+)x(\d+): (\d+) (\d+) (\d+) (\d+) (\d+) (\d+))");

    // for (auto item: items)
    // {
    //     for (auto k : aoc::range(3))
    //     {
    //         cout << item[k][0] << item[k][1] << item[k][2] << "\n";
    //     } 
    //     cout << "\n";
    // }

    // for (auto [x, y, a, b, c, d, e, f] : boxes)
    // {
    //     cout << x << " " << y << " " << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
    // }


    // Read all lines from a file into a vector of strings. Trims lines by default and drops empty lines by default. Keeping
    // empty lines can be useful when the blank lines in the input are meaningful.
    // std::vector<std::string> read_lines(std::string filename, Blanks allow_blanks = Blanks::Suppress, Trim trim_lines = Trim::Yes);

    auto p1 = part1(boxes, items);
    cout << "Part1: " << p1 << '\n';

    // auto p2 = part2();
    // cout << "Part2: " << p2 << '\n';
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
