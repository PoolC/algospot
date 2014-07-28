#include <iostream>
#include <string>
#include <stack>

#ifdef _DEBUG
#include <sstream>
std::stringstream debug_stream("3 ()() ({[}]) ({}[(){}])");
#define input debug_stream
#else
#define input std::cin
#endif

static bool brackets2(const std::string& test);

int main(int argc, char* argv[]) {
    int count;
    input >> count;
    while (count-- > 0) {
        std::string line;
        input >> line;
        std::cout << (brackets2(line) ? "YES" : "NO") << std::endl;
    }
    return 0;
}

static bool brackets2(const std::string& test) {
    std::stack<char> stack;
    for (char ch : test) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
            continue;
        }

        if (stack.empty()) return false;

        char top = stack.top();
        if (ch == ')' && top != '(') return false;
        else if (ch == '}' && top != '{') return false;
        else if (ch == ']' && top != '[') return false;
        stack.pop();
    }
    return stack.empty();
}
