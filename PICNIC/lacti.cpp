#include <iostream>
#include <bitset>
#include <sstream>

#pragma region ADT
template <size_t count>
struct bitmap
{
    typedef std::bitset<count * count> storage_t;

    bitmap()
        : size(0) {}

    int  index(int x, int y) const { return x + y * size; }
    bool test(int x, int y)  const { return storage[index(x, y)]; }
    void set(int x, int y)   { storage[index(x, y)] = true; }
    void reset(int x, int y) { storage[index(x, y)] = false; }

    storage_t  storage;
    int        size;
};

template <size_t count>
struct bitset_acquire
{
    typedef std::bitset<count> storage_t;

    bitset_acquire(storage_t& _storage, size_t _pos)
        : storage(_storage), pos(_pos), acquired(!_storage.test(_pos))
    {
        if (acquired)
            storage.set(pos);
    }

    ~bitset_acquire()
    {
        if (acquired)
            storage.reset(pos);
    }

    storage_t& storage;
    bool       acquired;
    size_t     pos;
};
#pragma endregion

#pragma region Iterating Helper
template <typename _Func>
void range(int start, int end, _Func&& functor)
{
    for (; start < end; ++start)
        functor(start);
}

template <typename _Func>
void repeat(int count, _Func&& functor)
{
    for (; count-- > 0;)
        functor();
}
#pragma endregion

#pragma region Input
#ifdef _DEBUG
std::stringstream test_in(
    "3    2 1   0 1    4 6   0 1 1 2 2 3 3 0 0 2 1 3    6 10    0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5"
);
#define INPUT   test_in
#else
#define INPUT   std::cin
#endif

template <typename _Ty>
_Ty input()
{
    _Ty var;
    INPUT >> var;
    return var;
}
#undef INPUT
#pragma endregion

static const int max_input_count = 50;
typedef bitmap<max_input_count>         friend_map_t;
typedef std::bitset<max_input_count>	grouped_set_t;
typedef bitset_acquire<max_input_count> grouped_acq_t;

static int count_case(const friend_map_t& friend_map, grouped_set_t grouped, int start_index)
{
    int count = 0;
    range(start_index, friend_map.size - 1, [&] (int first)
    {
        grouped_acq_t first_acq(grouped, first);
        if (!first_acq.acquired) return;

        range(first + 1, friend_map.size, [&] (int second)
        {
            grouped_acq_t second_acq(grouped, second);
            if (!second_acq.acquired) return;
            if (!friend_map.test(first, second) && !friend_map.test(second, first)) return;

            if (grouped.all()) ++count;
            else count += count_case(friend_map, grouped, first + 1);
        });
    });
    return count;
}

int main(int argc, char* argv[])
{
    repeat(input<int>(), [=] ()
    {
        friend_map_t friend_map;
        friend_map.size = input<int>();

        grouped_set_t grouped;
        grouped.flip();
        range(0, friend_map.size, [&grouped] (int index) { grouped.reset(index); });
        repeat(input<int>(), [&friend_map] { friend_map.set(input<int>(), input<int>()); });

        std::cout << count_case(friend_map, grouped, 0) << std::endl;
    });
    return 0;
}