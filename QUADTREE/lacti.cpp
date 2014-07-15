#include <iostream>
#include <vector>

typedef std::vector<char> result_t;
const int max_length = 1000;

static void reverse(const char*& input, result_t& output);

int main(int argc, char* argv[])
{
    int count;
	std::cin >> count;
	std::cin.ignore(1024, '\n');

	char buffer[max_length];

	result_t output;
	output.reserve(max_length);
	while (--count >= 0)
	{
		std::cin.getline(buffer, max_length);

		output.clear();
		
		const char* iter = buffer;
		reverse(iter, output);
		output.push_back(0);

		std::cout << &output.front() << std::endl;
	}
	
	return 0;
}

static void reverse(const char*& input, result_t& output)
{
	char current = *input++;
	if (current == 'w' || current == 'b')
	{
		output.push_back(current);
		return;
	}

	output.push_back('x');
	result_t uppers;
	uppers.reserve(max_length);
	/* 1 */ reverse(input, uppers); /* 2 */ reverse(input, uppers);
	/* 3 */ reverse(input, output); /* 4 */ reverse(input, output);
	output.insert(output.end(), uppers.begin(), uppers.end());
}
