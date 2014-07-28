#include <iostream>
#include <vector>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("2   4  1  1 1   1 1 1   1 1 1 1    4  9  5 7  1 3 2  3 5 5 6");
#define input debug_stream
#else
#define input std::cin
#endif

struct memory_cell_t {
    int sum;
    int count;
    memory_cell_t()
        : sum(0), count(0) {}
};

typedef std::vector<int> tree_t;
typedef std::vector<memory_cell_t> memory_t;

static int tripathcnt(const tree_t& tree, int height);

int main(int argc, char* argv[]) {
    int count;
    input >> count;
    while (count-- > 0) {
        int height;
        input >> height;
        tree_t tree(height * (height + 1) / 2);
        for (int& element : tree) {
            input >> element;
        }
        std::cout << tripathcnt(tree, height) << std::endl;
    }
    return 0;
}

static int tripathcnt(const tree_t& tree, int height) {
    memory_t memory(tree.size());

    // fill leafs memory
    int leaf_index = height * (height - 1) / 2;
    for (int offset = 0; offset < height; ++offset) {
        memory_t::value_type& leaf_cell = memory[leaf_index + offset];
        leaf_cell.sum = tree[leaf_index + offset];
        leaf_cell.count = 1;
    }

    // iterate tree nodes reversely(bfs) with finding and counting max-sum-path
    for (int level = height - 1; level >= 0; --level) {
        int index = level * (level - 1) / 2;
        int child_index = level * (level + 1) / 2;
        for (int offset = 0; offset < level; ++offset) {
            const tree_t::value_type& node_value = tree[index + offset];
            memory_t::value_type& node_cell = memory[index + offset];
            memory_t::value_type& left_child = memory[child_index + offset];
            memory_t::value_type& right_child = memory[child_index + offset + 1];

            if (left_child.sum > right_child.sum) {
                node_cell.sum = node_value + left_child.sum;
                node_cell.count = left_child.count;
            }
            else if (left_child.sum < right_child.sum) {
                node_cell.sum = node_value + right_child.sum;
                node_cell.count = right_child.count;
            }
            else {
                node_cell.sum = node_value + left_child.sum;
                node_cell.count = left_child.count + right_child.count;
            }
        }
    }
    return memory[0].count;
}
