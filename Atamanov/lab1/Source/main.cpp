#include <iostream>
class Combination{
	
public:
	unsigned long long int C = 0;
	int n;
	int m;
	unsigned long long int combination(int n, int m){
    if((m == 0 && n>0) || (m == n && n>=0))
		return 1;
	else if(m > n && n >=0)
		return 0;
	else
		return combination(n-1, m-1) + combination(n-1, m);
    }
};

int main(int argc, char* argv[]){
	Combination newton;
	if(argc!=3){
		std::cout << "Don't have enough argument's\n";
		return 0;
	}
	newton.n = atoi(argv[1]);
	newton.m = atoi(argv[2]);

	newton.C = newton.combination(newton.n, newton.m);
	std::cout << newton.C << "\n";
	return 0;
}
