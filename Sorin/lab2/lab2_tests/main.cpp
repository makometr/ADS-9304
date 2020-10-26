
#include <stdexcept>
#include <string>
#include "../src/calc.h"
#include <fstream>
int main() {
	try
	{
		double currect_results[] = { 3, 2, 5, 1, 15, 0, 0 };
		h_list<double> L;
		calk<double> C(L);
		double Res;
		std::string Str;
		//* Test 1
		std::ifstream InTest1("../tests/test_in/in1.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[0])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 2
		std::ifstream InTest1("../tests/test_in/in2.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[1])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 3
		std::ifstream InTest1("../tests/test_in/in3.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[2])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 4
		std::ifstream InTest1("../tests/test_in/in4.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[3])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 5
		std::ifstream InTest1("../tests/test_in/in5.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[4])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 6
		std::ifstream InTest1("../tests/test_in/in6.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[6])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		/* Test 7
		std::ifstream InTest1("../tests/test_in/in7.txt");
		if (InTest1.is_open())
		{
			if (!std::getline(InTest1, Str))
				throw std::runtime_error("Error while reading from stream");
		}
		std::stringstream Stream(Str);
		C.ReadExpr(Stream);
		Res = C.CalcExpr();
		std::cout << '\n' << Res << '\n';
		if (Res == currect_results[6])
			std::cout << '\n' << "test passed" << '\n';
		else
			std::cout << '\n' << "test failed" << '\n';
		//*/
		system("pause");
	}
	catch (const std::exception& Error)
	{
		std::cout << '\n' << Error.what();
		std::cout << '\n' << "test failed" << '\n';
	}
	return 0;
}