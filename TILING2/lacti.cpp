#include <iostream>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("3 1 5 100");
#define input debug_stream
#else
#define input std::cin
#endif

// solve the tiling2 problem using template meta programming for complie-time calculation
template <int N>
struct tiling2 {
    static const int value = (tiling2<N - 1>::value + tiling2<N - 2>::value) % 1000000007;
};
template <> struct tiling2<1> { static const int value = 1; };
template <> struct tiling2<2> { static const int value = 2; };

// cache tiling2 result to array for access values at runtime
static const int max_cases = 100;
static int tiling2_values[max_cases + 1];

template <int N>
void init() {
    tiling2_values[N] = tiling2<N>::value;
    init<N - 1>();
}
template <> void init<0>() {}

int main(int argc, char* argv[]) {
    init<max_cases>();

    int count;
    input >> count;
    while (count-- > 0) {
        int number;
        input >> number;

        std::cout << tiling2_values[number] << std::endl;
    }
    return 0;
}
