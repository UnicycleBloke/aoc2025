#include "utils.h"


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;

    int pass = 0;  
    int pos  = 50;  
    for (auto [dir, count]: input)
    {
        if (dir == 'R')
        {
            pos = (pos + count) % 100;
        }
        else
        {
            pos = (pos + 100 - count) % 100;
        }

        pass += (pos == 0);  
    }

    return pass;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;

    int pass = 0;  
    int pos  = 50;  
    for (auto [dir, count]: input)
    {
        if (dir == 'R')
        {
            for (auto i: aoc::range(count))
            {
                pos = (pos + 1) % 100;
                pass += (pos == 0);  
            }
        }
        else
        {
            for (auto i: aoc::range(count))
            {
                pos = (pos + 99) % 100;
                pass += (pos == 0);  
            }
        }
    }

    return pass;
}


void run(const char* filename)
{
    //template <class... Args>
    //std::vector<std::tuple<Args...>> read_lines(std::string filename, std::string pat, const std::string& delim = ";")
    auto lines = aoc::read_lines<char, int>(filename, R"((\w)(\d+))");

    // Read all lines from a file into a vector of strings. Trims lines by default and drops empty lines by default. Keeping 
    // empty lines can be useful when the blank lines in the input are meaningful.
    //std::vector<std::string> read_lines(std::string filename, Blanks allow_blanks = Blanks::Suppress, Trim trim_lines = Trim::Yes);

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
