
#include <iostream>

int main(void){
	
	char* ptr;
	char arr[10000] = {0};
	int testNum = 0;
	char enq;
	bool is = true;

	std::cin >> testNum;
	while(testNum){

		ptr = arr;
		is = true;

		std::cin >> enq;
		while( enq != '\n'){
			switch(enq){
			case '(' :case '{' : case '[' : *(ptr++) = enq; break;

			case ')' : if( *(ptr-1) != '(' ){ is = false; break;}else{ *(ptr--) = 0; break;}
			case '}' : if( *(ptr-1) != '{' ){ is = false; break;}else{ *(ptr--) = 0; break;}
			case ']' : if( *(ptr-1) != '[' ){ is = false; break;}else{ *(ptr--) = 0; break;}
			}
			enq = getchar();
		}

		if( ptr != &arr[0] )
			 is = false;

		switch(is){
		case true : std::cout << "YES" << std::endl; break;
		case false : std::cout << "NO" << std::endl; break;
		}

		testNum--;
	}
	return 0;
}