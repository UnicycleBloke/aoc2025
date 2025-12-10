#include "utils.h"


struct Machine
{
    uint64_t         target{};
    vector<uint64_t> buttons{};
    vector<uint16_t> joltage;

    vector<vector<uint16_t>> buttons2;

    void print() const
    {
        cout << "[" << bitset<8>{target} << "] ";
        for (auto button: buttons)
            cout << "(" << bitset<8>{button} << ") ";
        cout << "{";    
        for (auto j: joltage)
            cout << j << ",";
        cout << "}\n";
    }
};


void toggle(uint64_t target, uint64_t state, uint16_t steps, uint64_t prev_button, 
    const Machine& machine, uint16_t& max_steps, vector<uint64_t> path)
{
    if (steps >= max_steps)
        return;

    if (target == state)
    {
        max_steps = std::min(max_steps, steps);
        // cout << steps << " ";
        // for (auto p: path)
        //     cout << "(" << bitset<8>{p} << ") ";
        // cout << "\n";
        return;
    }

    for (auto button: machine.buttons)
    {
        //if (button == prev_button) continue;
        auto path2 = path;
        path2.push_back(button);
        toggle(target, state ^ button, steps + 1, button, machine, max_steps, path2);
    }
}


template <typename T>
auto part1(const T& input)
{
    aoc::timer timer;
    uint64_t result = 0;

    for (const auto& machine: input)
    {
        machine.print();
        uint16_t max_steps = machine.buttons.size();
        vector<uint64_t> path;
        toggle(machine.target, 0, 0, 0, machine, max_steps, path);
        result += max_steps;
        cout << max_steps << "\n";
    }

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
    auto lines = aoc::read_lines(filename, aoc::Blanks::Suppress, aoc::Trim::Yes);

    vector<Machine> machines;
    for (auto line: lines)
    {
        Machine machine;

        auto s = aoc::split(line, " ");

        size_t lights = s[0].size() - 2U;

        for (auto t: s)
        {           
            if (t[0] == '[')
            {
                size_t i = 1;
                while (t[i] != ']')
                {
                    machine.target *= 2;
                    if (t[i] == '#')
                        machine.target += 1;
                    ++i;
                }
            }

            if (t[0] == '(')
            {               
                size_t i = 1;
                uint64_t button = 0;
                vector<uint16_t> button2;

                while (t[i] != ')')
                {
                    if (t[i] == ',') ++i;

                    int value = 0;
                    while (isdigit(t[i]))
                    {
                        value *= 10;
                        value += t[i] - '0';
                        ++i; 
                    }  
                    button |= (1 << (lights - value - 1));
                    button2.push_back(value);
                }
                machine.buttons.push_back(button);
                machine.buttons2.push_back(button2);
            }

            if (t[0] == '{')
            {
                size_t i = 1;
                vector<uint16_t> joltage;
                while (t[i] != '}')
                {
                    if (t[i] == ',') ++i;

                    int value = 0;
                    while (isdigit(t[i]))
                    {
                        value *= 10;
                        value += t[i] - '0';
                        ++i; 
                    }
                    machine.joltage.push_back(value);
                }
            }
            
        }

        machines.push_back(machine);
    }

    auto p1 = part1(machines);
    cout << "Part1: " << p1 << '\n';

    auto p2 = part2(machines);
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
