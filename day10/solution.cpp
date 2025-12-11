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
        // for (auto button: buttons)
        //     cout << "(" << bitset<8>{button} << ") ";
        for (auto button: buttons2)
        {
            cout << "(";
            for (auto b: button) cout << b << " ";
            cout << ") ";
        }
        cout << "{";    
        for (auto j: joltage)
            cout << j << ",";
        cout << "}\n";
    }
};


// void toggle(const Machine& machine, uint64_t state, uint16_t index, uint16_t steps, uint16_t& min_steps)
// {
//     if (index >= machine.buttons.size()) return;

//     if (steps >= min_steps) return;

//     if (machine.target == state)
//     {
//         min_steps = std::min(min_steps, steps);
//         return;
//     }

//     toggle(machine, state,                          index + 1, steps,     min_steps);
//     toggle(machine, state ^ machine.buttons[index], index + 1, steps + 1, min_steps);
// }


// template <typename T>
// auto part1(const T& input)
// {
//     aoc::timer timer;
//     uint64_t result = 0;

//     for (const auto& machine: input)
//     {
//         machine.print();
//         uint16_t min_steps = machine.buttons.size();
//         toggle(machine, 0, 0, 0, min_steps);
//         result += min_steps;
//         cout << min_steps << "\n";
//     }

//     return result;
// }


// [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
// [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
// [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}

void increment(const Machine& machine, vector<uint16_t> state, uint16_t index, uint16_t steps, uint16_t& min_steps, vector<uint16_t> path)
{
    if (index >= machine.buttons2.size()) 
        return;

    if (steps >= min_steps)
        return;

    while (true)
    {
        const auto& lights = machine.buttons2[index];
        for (auto i: lights)
        {
            ++state[i];
            if (state[i] > machine.joltage[i])
                return;                 
        }
        
        path.push_back(index);    

        if (state == machine.joltage)
        {
            min_steps = std::min(min_steps, steps);

            for (auto j: path) cout << j << " ";
            cout << "\n";

            return;
        }
        else 
        {
            increment(machine, state, index + 1, steps + 1, min_steps, path);
        }

        ++steps; 
    }
}


template <typename T>
auto part2(T& input)
{
    aoc::timer timer;
    uint64_t result = 0;

    for (const auto& machine: input)
    {
        //machine.print();

        cout << machine.buttons2.size() << " " << machine.joltage.size() << "\n";

        // vector<uint16_t> state(machine.joltage.size(), 0);

        // uint16_t min_steps = 1000;
        // vector<uint16_t> path;
        // increment(machine, state, 0, 0, min_steps, path);

        // result += min_steps;
        // cout << min_steps << "\n";
    }

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

    // auto p1 = part1(machines);
    // cout << "Part1: " << p1 << '\n';

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
