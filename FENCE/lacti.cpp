#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("3   7  7 1 5 9 6 7 3   7  1 4 4 4 4 1 1   4  1 8 2 2");
#define input debug_stream
#else
#define input std::cin
#endif

typedef std::vector<int> fence_t;

static int find_max_area(const fence_t& fence, int left, int right);

int main(int argc, char* argv[]) {
    int count = 0;
    input >> count;

    while (count-- > 0) {
        int fence_count = 0;
        input >> fence_count;

        fence_t fence(fence_count);
        for (int index = 0; index < fence_count; ++index)
            input >> fence[index];

        std::cout << find_max_area(fence, /* left = */ 0, /* right = */ fence.size() - 1) << std::endl;
    }
    return 0;
}

static int find_max_area(const fence_t& fence, int left, int right) {
    if (left == right)
        return fence[left];

    // divide left & right cases
    int mid = (left + right) / 2;
    int left_side = find_max_area(fence, left, mid);
    int right_side = find_max_area(fence, mid + 1, right);

    // find a case containing the middle point
    int middle_left = mid;
    int middle_right = mid + 1;
    int middle_side = 0;
    int middle_height = std::numeric_limits<int>::max();
    while (middle_left >= left && middle_right <= right) {
        middle_height = std::min(middle_height, std::min(fence[middle_left], fence[middle_right]));
        middle_side = std::max(middle_side, middle_height * (middle_right - middle_left + 1));

        if (middle_left == left) ++middle_right;
        else if (middle_right == right) --middle_left;
        else {
            if (fence[middle_left - 1] < fence[middle_right + 1]) ++middle_right;
            else --middle_left;
        }
    }
    return std::max(left_side, std::max(right_side, middle_side));
}
