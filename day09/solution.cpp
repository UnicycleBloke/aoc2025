#include "utils.h"


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;
    int64_t result = 0;

    // Simple scan of all possible pairs of points.
    auto size = input.size();
    for (auto i: aoc::range(size))
    {
        auto [xi, yi] = input[i];
        for (auto j: aoc::range(i + 1, size))
        {
            auto [xj, yj] = input[j];
            auto area = (abs(xj - xi) + 1) * (abs(yi - yj) + 1);
            result = max(result, area);
        }
    }

    return result;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    int64_t result = 0;

    auto size = input.size();
    for (auto i: aoc::range(size))
    {
        auto [xi, yi] = input[i];
        for (auto j: aoc::range(i + 1, size))
        {
            auto [xj, yj] = input[j];

            // This function is sloooooow. It walks the boundary line to test
            // whether it goes inside the current rectangle. I was expecting a
            // corner case in which the boundary creates an inclusion of zero width,
            // but seem to have got away with it. 
            // auto has_points_inside = [&]()
            // {
            //     auto [x, y] = input[0];
            //     // +1 to complete the boundary loop. Note use of % below.
            //     for (auto k: aoc::range(size + 1U))
            //     {
            //         auto [xk, yk] = input[k % size];
            //         auto xd = aoc::sgn(xk - x);
            //         auto yd = aoc::sgn(yk - y);
            //         while ((x != xk) || (y != yk))
            //         {
            //             x += xd;
            //             y += yd;
              
            //             if ( (x > min(xi, xj)) && 
            //                  (x < max(xi, xj)) && 
            //                  (y > min(yi, yj)) && 
            //                  (y < max(yi, yj)))
            //                 return true;
            //         }
            //     }
            //     return false;
            // };

            // This function is much faster as it tests only the midpoint of each
            // line on the boundary. If the midpoint lies inside the rectangle, we're done. 
            auto has_points_inside = [&]()
            {
                auto [x, y] = input[0];
                // +1 to complete the boundary loop. Note use of % below.
                for (auto k: aoc::range(size + 1U))
                {
                    auto [xk, yk] = input[k % size];
                    x = (xk + x) / 2;
                    y = (yk + y) / 2;
             
                    if ( (x > min(xi, xj)) && 
                            (x < max(xi, xj)) && 
                            (y > min(yi, yj)) && 
                            (y < max(yi, yj)))
                        return true;

                    x = xk;
                    y = yk;
                }
                return false;
            };

            if (has_points_inside()) continue;

            auto area = (abs(xj - xi) + 1) * (abs(yi - yj) + 1);
            result = max(result, area);
        }
    }

    return result;
}


void run(const char* filename)
{
    auto lines = aoc::read_lines<int64_t, int64_t>(filename, R"((\d+),(\d+))");

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
