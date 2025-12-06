#include "utils.h"


template <typename T, typename U>
auto part1(const T& numbers, const U& ops)
{
    aoc::timer timer;
    uint64_t total = 0;

    for (auto i: aoc::range(numbers[0].size()))
    {
        if (ops[i] == '+')
        {
            uint64_t result = 0;
            for (const auto& n: numbers)
                result += n[i];
            total += result; 
        }
        else if (ops[i] == '*')
        {
            uint64_t result = 1;
            for (const auto& n: numbers)
                result *= n[i];
            total += result; 
        }
    }

    return total;
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    uint64_t total = 0;

    auto rows = input.size() - 1;
    const auto& ops = input[rows];

    // Find a vertical number at the given index. This will return 
    // zero when we reach a blank column. There appear to be no zeroes
    // in the intended input, so we can live with this. Easy to add a 
    // test for this condition, if necessary.
    auto find_number = [&](size_t i)
    {
        uint64_t value = 0;
        for (auto r: aoc::range(rows))
        {
            char d = input[r][i];
            if (isdigit(d))
            {
                value = value * 10 + (d - '0');
            }
        }
        return value;
    };

    // Walk the operator line. Each operator starts a new calculation.
    // The characters in this line drive a simple state machine to compute
    // sums and products, and then add them to the running total.
    char     op = ' ';
    uint64_t value = 0;
    for (auto index: aoc::range(ops.size()))
    {
        // Test for the start of a new calculation.
        switch (ops[index])
        {
            case '+':
                total += value;
                value  = 0;
                op     = '+';
                break;

            case '*':
                total += value;
                value  = 1;
                op     = '*';
                break; 
        }

        // Continue the current calculation. 
        uint64_t number = find_number(index); 
        switch (op)
        {
            case '+':
                value += number;
                break;

            case '*':
                // Ugh! Special case for when the column of digits is blank.
                if (number != 0)
                    value *= number;
                break; 
        }

        ++index;
    }

    // This is a bit untidy. Deal with the calculation in progress
    // at the end of the operator line.
    total += value;

    return total;
}


void run(const char* filename)
{
    // Trimming the input lines buggers up the indexing in Part2.
    auto lines = aoc::read_lines(filename, aoc::Blanks::Suppress, aoc::Trim::No);

    // Made a bit of a meal of this input for Part1, but it worked.
    vector<vector<uint64_t>> numbers;  
    for (auto i: aoc::range(lines.size() - 1))
    {
        auto items = aoc::make_vector<uint64_t>(lines[i], " ");
        numbers.push_back(items);
        cout << items.size() << " ";
    }
    auto ops = aoc::make_vector<char>(lines[lines.size() - 1], " ");
    cout << ops.size() << " ";

    auto p1 = part1(numbers, ops);
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
