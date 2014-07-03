#include <iostream>
#include <algorithm>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("2  12 6 6 6 6 6 12 12 12 12 12 12 12 12 12 12  12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6");
#define input debug_stream
#else
#define input std::cin
#endif

// define data structures
const int inf = 88888888;
const int clock_count = 16;
typedef int clocks_t[clock_count];

// define switchs
const int switch_count = 10;
const int switch_clock_count = 6;
int switches[switch_count][switch_clock_count] = {
    { 0, 1, 2, -1 }, { 3, 7, 9, 11, -1 }, { 4, 10, 14, 15, -1 }, { 0, 4, 5, 6, 7, -1 }, { 6, 7, 8, 10, 12, -1 },
    { 0, 2, 14, 15, -1 }, { 3, 14, 15, -1 }, { 4, 5, 7, 14, 15, -1 }, { 1, 2, 3, 4, 5, -1 }, { 3, 4, 5, 9, 13, -1 }
};

static int count_cases(clocks_t& clocks, int current_count);
static void push_swtich(clocks_t& clocks, int switch_index);
static bool is_matched(const clocks_t& clocks);

int main(int argc, char* argv[])
{
    int count = 0;
    input >> count;
    while (count-- > 0)
    {
        clocks_t clocks = { 0, };
        for (int index = 0; index < clock_count; ++index)
            input >> clocks[index];

        int count = count_cases(clocks, 0);
        if (count == inf)
            count = -1;
        std::cout << count << std::endl;
    }
    return 0;
}

static int count_cases(clocks_t& clocks, int switch_index)
{
    // check a base case
    if (is_matched(clocks))
        return 0;

    // if end-of-switch, problem can't be solved
    if (switch_index == switch_count)
        return inf;

    int total_push_count = inf;

    // it's meaningless that pushs switch more than 4-times.
    const int max_push_count = 4;
    for (int push_count = 0; push_count < max_push_count; ++push_count)
    {
        // find minimum count
        int sub_push_count = count_cases(clocks, switch_index + 1);
        total_push_count = std::min(total_push_count, sub_push_count + push_count);

        // push switch
        push_swtich(clocks, switch_index);
    }
    return total_push_count;
}

static void push_swtich(clocks_t& clocks, int switch_index)
{
    for (int switch_clock = 0; switch_clock < switch_clock_count; ++switch_clock)
    {
        if (switches[switch_index][switch_clock] == -1)
            break;
        int clock_index = switches[switch_index][switch_clock];

        // push and check overflow
        clocks[clock_index] = (clocks[clock_index] + 3) % 12;
        if (clocks[clock_index] == 0)
            clocks[clock_index] = 12;
    }
}

static bool is_matched(const clocks_t& clocks)
{
    for (int index = 0; index < clock_count; ++index)
    {
        if (clocks[index] != 12)
            return false;
    }
    return true;
}
