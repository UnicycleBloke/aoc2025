#include "utils.h"


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;
    int result = 0;

    return result;
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
    //template <class... Args>
    //std::vector<std::tuple<Args...>> read_lines(std::string filename, std::string pat, const std::string& delim = ";")
    auto lines = aoc::read_lines<int,int>(filename, R"((\d+)\s+(\d+))");

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
