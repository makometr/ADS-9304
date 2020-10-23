
#include <stdexcept>
#include <string>
#include "Calc.h"

int main()
{
	try
	{
		h_list<double> L;
		calk<double> C(L);
		double Res;
		std::string Str;
		if (!std::getline(std::cin, Str))
			throw std::runtime_error("Error while reading from stream");
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		system("pause");
	}
	catch (const std::exception& Error)
	{
		std::cout << '\n' << Error.what();
	}
	return 0;
}