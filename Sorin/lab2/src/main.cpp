
#include <stdexcept>
#include "Calc.h"

int main()
{
	try
	{
		h_list<double> L;
		calk<double> C(L);
		double Res;
		C.ReadExpr();
		Res = C.CalcExpr();
		std::cout << '\n' << Res;
		system("pause");
	}
	catch (const std::exception& Error)
	{
		std::cout << '\n' << Error.what();
	}
	return 0;
}