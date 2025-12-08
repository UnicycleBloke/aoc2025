#include "utils.h"


template <typename T>
auto part1(const T& boxes)
{
    aoc::timer timer;
    int result = 0;

    using Pair = tuple<uint64_t, size_t, size_t>;
    vector<Pair> pairs;

    for (auto i: aoc::range(boxes.size()))
    {
        auto [xi, yi, zi] = boxes[i];
        for (auto j: aoc::range(i + 1U, boxes.size()))
        {
            auto [xj, yj, zj] = boxes[j];
            auto dx = (xj - xi) * (xj - xi);
            auto dy = (yj - yi) * (yj - yi);
            auto dz = (zj - zi) * (zj - zi);
            auto dist = dx + dy + dz; 

            pairs.push_back(make_tuple(dist, i, j));
        }
    }

    using Circuit = set<size_t>;
    vector<Circuit> circuits;

    sort(pairs.begin(), pairs.end());

    const size_t kConnections = (boxes.size() > 20U) ? 1000U : 10U;
    for (auto p: aoc::range(pairs.size()))
    {
        auto [d, i, j] = pairs[p];
        
        size_t ci = -1;
        size_t cj = -1;
        for (auto c: aoc::range(circuits.size()))
        {
            if (circuits[c].find(i) != circuits[c].end())
                ci = c;
            if (circuits[c].find(j) != circuits[c].end())
                cj = c;
        }

        if ((ci == -1) && (cj == -1))
        {
            Circuit circuit;
            circuit.insert(i);
            circuit.insert(j);
            circuits.push_back(circuit);
        }
        else if (ci == -1)
        {
            circuits[cj].insert(i);

            if (circuits[cj].size() == boxes.size())
            {
                auto [xi, yi, zi] = boxes[i];
                auto [xj, yj, zj] = boxes[j];
                cout << xi << " * " << xj << " = " << (xi * xj) << "\n";
                break;
            }
        }
        else if (cj == -1)
        {
            circuits[ci].insert(j);           

            if (circuits[ci].size() == boxes.size())
            {
                auto [xi, yi, zi] = boxes[i];
                auto [xj, yj, zj] = boxes[j];
                cout << xi << " * " << xj << " = " << (xi * xj) << "\n";
                break;
            }
        }
        else if (ci != cj)
        {
            for (auto x: circuits[ci])
                circuits[cj].insert(x);
            circuits[ci].clear();             

            if (circuits[cj].size() == boxes.size())
            {
                auto [xi, yi, zi] = boxes[i];
                auto [xj, yj, zj] = boxes[j];
                cout << xi << " * " << xj << " = " << (xi * xj) << "\n";
                break;
            }
        }

        if ((p + 1) == kConnections)
        {
            vector<size_t> sizes;
            for (const auto& c: circuits)
                sizes.push_back(c.size());
            sort(sizes.begin(), sizes.end(), std::greater<size_t>());

            cout << sizes[0] * sizes[1] * sizes[2] << "\n";
        }
    }

    return 0;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    int result = 0;

    return result;
}


void run(const char* filename)
{
    auto lines = aoc::read_lines<int64_t, int64_t, int64_t>(filename, R"((\d+),(\d+),(\d+))");

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
