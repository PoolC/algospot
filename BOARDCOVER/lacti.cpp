#include <iostream>
#include <cstring>

#ifdef _DEBUG
#include <fstream>
std::ifstream debug_stream("input.txt", std::ios_base::in);
#define input debug_stream
#else
#define input std::cin
#endif

// define data structure
struct board_t
{
    static const int max_cases = 20;
    bool data[max_cases][max_cases];
    int height;
    int width;

    board_t()
        : height(0), width(0)
    {
        memset(data, 0, sizeof(data));
    }
};

// define relative positions of rotated block
// set blocks to have the same origin (left-top)
const int rotation_count = 4;
const int rotation_pair_count = 3;
static int rotate_cases[rotation_count][rotation_pair_count][2 /* y, x */] = {
    { { 0, 0 }, { 1, 0 }, { 0,  1 } }, // ¦£
    { { 0, 0 }, { 0, 1 }, { 1,  1 } }, // ¦¤
    { { 0, 0 }, { 1, 0 }, { 1,  1 } }, // ¦¦
    { { 0, 0 }, { 1, 0 }, { 1, -1 } }  // ¦¥
};

static int count_cases(board_t& board);
static bool find_empty_pos(board_t& board, int& empty_y, int& empty_x);
static bool check_and_fill(board_t& board, int start_y, int start_x, int rotate);
static void remove(board_t& board, int start_y, int start_x, int rotate);

int main(int argc, char* argv[])
{
    int count = 0;
    input >> count;
    while (count-- > 0)
    {
        // allocate and input board (with margin)
        board_t board;
        input >> board.height >> board.width;

        // input table (skip margin)
        for (int y = 0; y < board.height; ++y)
        {
            for (int x = 0; x < board.width; ++x)
            {
                char marker;
                input >> marker;
                board.data[y][x] = marker == '.';
            }
        }

        // solve problem
        int count = count_cases(board);
        std::cout << count << std::endl;
    }
    return 0;
}

static int count_cases(board_t& board)
{
    int y = 0, x = 0;

    // when all blocks is filled, problem is solved.
    if (!find_empty_pos(board, y, x))
        return 1;

    // put, count, and remove with iterating rotatable blocks
    int count = 0;
    for (int rotate = 0; rotate < rotation_count; ++rotate)
    {
        if (!check_and_fill(board, y, x, rotate))
            continue;

        count += count_cases(board);
        remove(board, y, x, rotate);
    }
    return count;
}

static bool find_empty_pos(board_t& board, int& empty_y, int& empty_x)
{
    for (int y = 0; y < board.height; ++y)
    {
        for (int x = 0; x < board.width; ++x)
        {
            // find a start point (empty cell)
            if (board.data[y][x])
            {
                empty_y = y;
                empty_x = x;
                return true;
            }
        }
    }
    return false;
}

template <typename _Func>
static bool work_with_rotating(board_t& board, int y, int x, int rotate, _Func&& functor)
{
    for (int offset = 0; offset < rotation_pair_count; ++offset)
    {
        int rotate_y = y + rotate_cases[rotate][offset][0];
        int rotate_x = x + rotate_cases[rotate][offset][1];
        if (rotate_y < 0 || rotate_x < 0 || rotate_y >= board.height || rotate_x >= board.width)
            return false;

        if (!functor(board, rotate_y, rotate_x))
            return false;
    }
    return true;
}

static bool check_and_fill(board_t& board, int y, int x, int rotate)
{
    // check if fillable
    bool is_empty = work_with_rotating(board, y, x, rotate, 
        [](const board_t& board, int y, int x) { return board.data[y][x]; });
    if (!is_empty)
        return false;

    // fill
    return work_with_rotating(board, y, x, rotate, 
        [](board_t& board, int y, int x) { board.data[y][x] = false; return true; });
}

static void remove(board_t& board, int y, int x, int rotate)
{
    work_with_rotating(board, y, x, rotate, 
        [](board_t& board, int y, int x) { board.data[y][x] = true; return true; });
}
