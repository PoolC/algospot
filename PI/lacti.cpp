#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

#ifdef _DEBUG
#include <sstream>
//std::stringstream debug_stream("5  12341234 11111222 12122222 22222222 12673939");
std::stringstream debug_stream("1  111113131357");
#define input debug_stream
#else
#define input std::cin
#endif

typedef std::vector<int> seq_t;

static int calc_difficulty(const seq_t& seq, seq_t& memory, int pos);
static int calc_difficulty(const seq_t& seq, int pos, int len);

int main(int argc, char* argv[]) {
    int count;
    input >> count;
    while (count-- > 0) {
        std::string line;
        input >> line;

        seq_t seq(line.size());
        seq_t memory(seq.size());
        std::transform(line.begin(), line.end(), seq.begin(), [](char ch) { return ch - '0'; });
        std::cout << calc_difficulty(seq, memory, /* pos = */ 0) << std::endl;
    }
    return 0;
}

enum difficulty_t {
    repeat    = 1,  // 1111 -> 0  0 0
    mono      = 2,  // 1234 -> 1  1 1
    duet      = 4,  // 1313 -> 2 -2 2
    equaldiff = 5,  // 1357 -> 2  2 2
    no_rule   = 10,
};

static int calc_difficulty(const seq_t& seq, seq_t& memory, int pos) {
    int seq_count = seq.size();
    if (pos == seq_count) return 0;
    if (memory[pos] != 0) return memory[pos];

    // calculate a difficulty sequence by each length
    int difficulty = 88888888; // inf
    for (int length = 3; length <= 5; ++length) {
        if (pos + length <= seq_count) {
            difficulty = std::min(difficulty,
                calc_difficulty(seq, memory, pos + length) + calc_difficulty(seq, pos, length));
        }
    }
    memory[pos] = difficulty;

    return difficulty;
}

template <typename _FwdIt, typename _Ty>
static bool are_all_elements_same(_FwdIt begin, _FwdIt end, _Ty& value) {
    value = *begin;
    for (_FwdIt it = begin; it != end; ++it) {
        _Ty current = *it;
        if (value != current)
            return false;
    }
    return true;
}

template <typename _FwdIt>
static bool is_duet(_FwdIt begin, _FwdIt end) {
    typename _FwdIt::value_type value = -1 * (*begin);
    for (_FwdIt it = ++begin; it != end; ++it) {
        typename _FwdIt::value_type current = *it;
        if (value != current)
            return false;
        value *= -1;
    }
    return true;
}

static int calc_difficulty(const seq_t& seq, int pos, int length) {
    seq_t interval(length - 1);
    for (int index = 1; index < length; ++index)
        interval[index - 1] = seq[pos + index] - seq[pos + index - 1];

    // check and return difficulty value using differernces in sequence
    int element;
    if (!are_all_elements_same(interval.begin(), interval.end(), element)) {
        if (is_duet(interval.begin(), interval.end()))
            return duet;
        return no_rule;
    }

    switch (element) {
    case 0:          return repeat;
    case 1: case -1: return mono;
    default:         return equaldiff;
    }
}
