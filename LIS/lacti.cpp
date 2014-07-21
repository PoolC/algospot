#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("3   4  1 2 3 4   8  5 4 3 2 1 6 7 8   8  5 6 7 8 1 2 3 4");
#define input debug_stream
#else
#define input std::cin
#endif

typedef std::vector<int> seq_t;

static int solve_lis(const seq_t& seq);
static void solve_lis(const seq_t& seq, seq_t& memory, int pos);

int main(int argc, char* argv[]) {
    int count;
    input >> count;
    while (count-- > 0) {
        int case_count;
        input >> case_count;
        seq_t seq(case_count);
        for (int index = 0; index < case_count; ++index)
            input >> seq[index];

        std::cout << solve_lis(seq) << std::endl;
    }
    return 0;
}

static int solve_lis(const seq_t& seq) {
    int seq_count = seq.size();
    seq_t memory(seq_count);
    // solve all lis cases
    while (true) {
        int zero_pos = -1;
        for (int index = 0; index < seq_count; ++index) {
            if (memory[index] == 0) {
                zero_pos = index;
                break;
            }
        }
        if (zero_pos == -1)
            break;
        solve_lis(seq, memory, zero_pos);
    }
    // find the maximum length
    auto max_it = std::max_element(memory.begin(), memory.end());
    return *max_it;
}

static void solve_lis(const seq_t& seq, seq_t& memory, int pos) {
    int seq_count = seq.size();
    for (int index = pos + 1; index < seq_count; ++index) {
        if (seq[pos] >= seq[index])
            continue;

        // yet not evaluating, solve recursively
        if (memory[index] == 0)
            solve_lis(seq, memory, index);
        // select a maximum case
        memory[pos] = std::max(memory[pos], memory[index] + 1);
    }
    // if there is no lis, that seq is a element
    if (memory[pos] == 0)
        memory[pos] = 1;
}
