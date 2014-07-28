#include <iostream>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("");
#define input debug_stream
#else
#define input std::cin
#endif

int main(int argc, char* argv[]) {
    int count;
    input >> count;
    while (count-- > 0) {
        
    }
    return 0;
}
