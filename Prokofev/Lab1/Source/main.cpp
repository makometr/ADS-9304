#include <iostream>
using namespace std;
int TextToInt(char *c)
{
	bool warning=0;
	int znak=1;
	int result=0;
	for(int i=0; i<(strlen(c)); i++)
	{
		if((c[i] == '-')&&(znak==1)&&(result==0)) znak*=(-1);
		if((c[i] >= '0') && (c[i] <= '9')) 
		{
			result=result*10+c[i]-'0';
		} else if(c[i] != '-') warning=1;
	}
	result*=znak;
	return result;
}
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
    res=TextToInt(vvod);
	if(res<1) cout << "not answer";
	cout << f(res);
	return 0;
}

