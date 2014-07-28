#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("3   8791 20  5265 5000  3578452 5000000");
#define input debug_stream
#else
#define input std::cin
#endif

typedef unsigned int uint;

static const uint ites_init = 1983;
inline uint generate_ites(uint prev)       { return prev * 214013 + 2531011; }
inline int  to_seq_number(uint ites_value) { return ites_value % 10000 + 1;  }

struct problem_context {
    int seq_count;    // N
    int case_count;   // answer
    int target_sum;   // K
    int sum;          // current-sum (for solving)
    uint partial_seq_first_ites;
    problem_context()
        : case_count(0), sum(0), partial_seq_first_ites(ites_init) {}
};

int main(int argc, char* argv[]) {
    int count;
    input >> count;

    // cache problems' context
    int max_seq_count = 0;
    std::vector<problem_context> contexts(count);
    for (problem_context& ctx : contexts) {
        input >> ctx.target_sum >> ctx.seq_count;
        max_seq_count = std::max(max_seq_count, ctx.seq_count);
    }

    // generate ites value and sequence and solve problem in parallel
    uint ites_value = ites_init;
    for (int seq_index = 0; seq_index < max_seq_count; ++seq_index) {
        int seq_number = to_seq_number(ites_value);

        for (problem_context& ctx : contexts) {
            if (ctx.seq_count < seq_index)
                continue;

            // calculate a sum of seq and check if both are same
            ctx.sum += seq_number;
            if (ctx.sum == ctx.target_sum) {
                ++ctx.case_count;
            }

            // if exceed, subtract front values from a sum of partial seq
            while (ctx.sum > ctx.target_sum) {
                ctx.sum -= to_seq_number(ctx.partial_seq_first_ites);
                ctx.partial_seq_first_ites = generate_ites(ctx.partial_seq_first_ites);

                // check while subtracting
                if (ctx.sum == ctx.target_sum)
                    ++ctx.case_count;
            }
        }
        ites_value = generate_ites(ites_value);
    }

    for (const auto& ctx : contexts) {
        std::cout << ctx.case_count << std::endl;
    }
    return 0;
}
