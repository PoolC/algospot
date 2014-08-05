
#include <iostream>
int main(void){
	
	long long int sum = 0;
	int test = 0;
	int num = 0;
	
	unsigned long long int Aorigin = 0;
	unsigned long long int Apresent = 0;

	long long int N;
	long long int K;

	std::cin >> test;
	while(test){
		std::cin >> K; std::cin >> N;
		Aorigin = 1983; Apresent = 1983;
		sum = 0; num = 0;

		while( N ){
			if( sum > K && sum >= (Aorigin%10000 + 1) ){
				sum -= Aorigin%10000 + 1; Aorigin = (Aorigin*214013 + 2531011)%4294967296;
			}else if( sum == K ){
				num++; sum -= Aorigin%10000 + 1; Aorigin = (Aorigin*214013 + 2531011)%4294967296;
				sum += (Apresent%10000 + 1); Apresent = (Apresent*214013 + 2531011)%4294967296;N--;
			}else if( sum < K ){
				sum += (Apresent%10000 + 1); Apresent = (Apresent*214013 + 2531011)%4294967296;N--;
			}
		}

		std::cout << num << std::endl;
	test--;
	}

	return 0;
}