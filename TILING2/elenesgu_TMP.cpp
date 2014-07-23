#include<cstdio>

using namespace std;

template<int T>
struct SN{
	static const int N = (SN<T - 1>::N + SN<T - 2>::N) % 1000000007;
};

template<>
struct SN<1> {
	static const int N = 1;
};

template<>
struct SN<2> {
	static const int N = 2;
};

int n, t, DM[100] {
	SN<1>::N, SN<2>::N, SN<3>::N, SN<4>::N, SN<5>::N, SN<6>::N, SN<7>::N, SN<8>::N, SN<9>::N, SN<10>::N,
	SN<11>::N, SN<12>::N, SN<13>::N, SN<14>::N, SN<15>::N, SN<16>::N, SN<17>::N, SN<18>::N, SN<19>::N, SN<20>::N,
	SN<21>::N, SN<22>::N, SN<23>::N, SN<24>::N, SN<25>::N, SN<26>::N, SN<27>::N, SN<28>::N, SN<29>::N, SN<30>::N,
	SN<31>::N, SN<32>::N, SN<33>::N, SN<34>::N, SN<35>::N, SN<36>::N, SN<37>::N, SN<38>::N, SN<39>::N, SN<40>::N,
	SN<41>::N, SN<42>::N, SN<43>::N, SN<44>::N, SN<45>::N, SN<46>::N, SN<47>::N, SN<48>::N, SN<49>::N, SN<50>::N,
	SN<51>::N, SN<52>::N, SN<53>::N, SN<54>::N, SN<55>::N, SN<56>::N, SN<57>::N, SN<58>::N, SN<59>::N, SN<60>::N,
	SN<61>::N, SN<62>::N, SN<63>::N, SN<64>::N, SN<65>::N, SN<66>::N, SN<67>::N, SN<68>::N, SN<69>::N, SN<70>::N,
	SN<71>::N, SN<72>::N, SN<73>::N, SN<74>::N, SN<75>::N, SN<76>::N, SN<77>::N, SN<78>::N, SN<79>::N, SN<80>::N,
	SN<81>::N, SN<82>::N, SN<83>::N, SN<84>::N, SN<85>::N, SN<86>::N, SN<87>::N, SN<88>::N, SN<89>::N, SN<90>::N,
	SN<91>::N, SN<92>::N, SN<93>::N, SN<94>::N, SN<95>::N, SN<96>::N, SN<97>::N, SN<98>::N, SN<99>::N, SN<100>::N
};



int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%d\n", DM[n - 1]);
	}
	return 0;
}