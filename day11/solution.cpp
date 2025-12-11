#include "utils.h"


// Original Part1 code 
// int count_paths(map<string, vector<string>>& devices, const string& src, const string& out)
// {
//     if (src == out) 
//         return 1;

//     int count = 0;
//     for (const auto& dst: devices[src])
//     {
//         count += count_paths(devices, dst, out);
//     }

//     return count;
// }


// More general solution using a cache.
uint64_t count_paths(map<string, vector<string>>& devices, 
    map<string, uint64_t>& counts, map<string, bool>& visited,
    const string& src, const string& end)
{
    if (src == end) 
        return 1;

    if (visited[src])
        return counts[src];

    uint64_t count = 0;
    for (const auto& dst: devices[src])
        count += count_paths(devices, counts, visited, dst, end);
    counts[src]  = count;
    visited[src] = true;

    return count;
}


uint64_t count_paths(map<string, vector<string>>& devices, const string& src, const string& dst)
{
    // A little dynamic programming to accumulate the numbers of paths.
    map<string, bool>     visited;
    map<string, uint64_t> counts;

    counts[dst] = 1;       
    auto result = count_paths(devices, counts, visited, src, dst);
    //cout << src << " -> " << end << " = " << result << "\n";
    return result;
}


template <typename T>
auto part1(T& input)
{
    aoc::timer timer;
    int result = 0;

    result = count_paths(input, "you", "out");

    return result;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    uint64_t result = 0;

    // All paths either go from dac to fft, or vice versa. We can't have both.
    // Determine the direction and then find paths piece-wise.
    result = count_paths(input, "dac", "fft");
    if (result == 0)
    {
        result  = count_paths(input, "svr", "fft");
        result *= count_paths(input, "fft", "dac");
        result *= count_paths(input, "dac", "out");
    }
    else
    {
        result  = count_paths(input, "svr", "dac");
        result *= count_paths(input, "dac", "fft");
        result *= count_paths(input, "fft", "out");
    }

    return result;
}


struct Device
{
    string         src;
    vector<string> dst;
};


void run(const char* filename)
{
    auto lines = aoc::read_lines(filename, aoc::Blanks::Suppress, aoc::Trim::Yes);

    //vector<Device> devices;

    map<string, vector<string>> devices;
    for (auto line: lines)
    {
        //Device d;

        auto s = aoc::split(line, ":");
        devices[s[0]] = aoc::split(s[1], " ");

        // d.src = s[0];
        // d.dst = aoc::split(s[1], " ");
        // devices.push_back(d);

        // cout << d.src << ": ";
        // for (const auto& t: d.dst)
        //     cout << t << " ";
        // cout << "\n";
    }

    auto p1 = part1(devices);
    cout << "Part1: " << p1 << '\n';

    auto p2 = part2(devices);
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
