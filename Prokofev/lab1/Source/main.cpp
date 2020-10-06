#include <iostream>
#include <stdlib.h> 

int f(int n)
{
	int sum=0, i=1, quantity=n-(n/3);
	if((n==2)||(n==1)) return 1;
	while((n/++i)>2) sum+=f(n/i);
	sum+=quantity;
	return sum;
}
int main()
{
	char vvod[256]; int res=0;
	gets(vvod);
	res=atoi(vvod);
	if(res<1) std::cout << "not answer";
	else std::cout << f(res);
	return 0;
}

