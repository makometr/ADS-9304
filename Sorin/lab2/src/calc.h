#ifndef __CALC
#define __CALC

#include "h_list.h"
#include <stdexcept>
#include <conio.h>
#include <sstream>


template <typename base>
class calk {
	std::shared_ptr<h_list<base>> H_List;
	base *VarValue['z' + 1];
	void H_ListToValueOfRoot(std::shared_ptr<h_list<base>> &L, std::shared_ptr<h_list<base>>& save) {
		std::shared_ptr<h_list<base>> Root = std::make_shared<h_list<base>>();
		Root->value = save;
		save = Root;
		L = save;
	}
	base ReadNumber(char k, std::stringstream& Stream) {
		base Num = 0;

		if (k == '0')
		{
			std::cout << '0';
			if (!Stream.get(k))
				throw std::invalid_argument("Error while entering expression");
			if (k == ',')
			{
				std::cout << ',';
				int I = 0;
				if (!Stream.get(k))
					throw std::invalid_argument("Error while entering expression");
				if (k < '0' || k > '9')
					throw std::invalid_argument("Error while entering expression");
				Num += 0.1 * ((base)k - '0');
				I++;
				std::cout << k;
				while (1)
				{
					if (!Stream.get(k))
						throw std::invalid_argument("Error while entering expression");
					if (k >= '0' && k <= '9')
					{
						base deg = 0.1;
						for (int i = 0; i < I; i++)
							deg /= 10;
						Num += deg * ((base)k - '0');
						I++;
						std::cout << k;
					}
					else if (k == ' ')
						return Num;
					else
						throw std::invalid_argument("Error while entering expression");
				}
			}
			else if (k == ' ')
				Num = 0;
			else
				throw std::invalid_argument("Error while entering expression");
			
			return Num;
		}
		if (k < '0' || k > '9')
			throw std::invalid_argument("Error while entering expression");
		Num += ((base)k - '0');
		std::cout << k;
		while (1)
		{
			if (!Stream.get(k))
				throw std::invalid_argument("Error while entering expression");
			if (k >= '0' && k <= '9')
			{
				Num *= 10;
				Num += ((base)k - '0');
				std::cout << k;
			}
			else if (k == ' ')
				return Num;
			else if (k == ',')
			{
				std::cout << ',';
				int I = 0;
				if (!Stream.get(k))
					throw std::invalid_argument("Error while entering expression");
				if (k < '0' || k > '9')
					throw std::invalid_argument("Error while entering expression");
				Num += 0.1 * ((base)k - '0');
				I++;
				std::cout << k;
				while (1)
				{
					if (!Stream.get(k))
						throw std::invalid_argument("Error while entering expression");
					if (k >= '0' && k <= '9')
					{
						base deg = 0.1;
						for (int i = 0; i < I; i++)
							deg /= 10;
						Num += deg * ((base)k - '0');
						I++;
						std::cout << k;
					}
					else if (k == ' ')
						return Num;
					else
						throw std::invalid_argument("Error while entering expression");
				}
			}
			else
				throw std::invalid_argument("Error while entering expression");
		}
	}
	void ReadNumberToH_List(std::shared_ptr<h_list<base>> tmp, char k, std::stringstream& Stream) {
		VarNum<base> Num;
		Num.IsVar = false;
		Num.IsOp = false;
		Num.Num = ReadNumber(k, Stream);
		tmp->value = Num;
		std::cout << ' ';
	}
	void ReadVar(std::shared_ptr<h_list<base>> tmp, char v, std::stringstream& Stream) {
		VarNum<base> V;
		V.IsVar = true;
		V.IsOp = false;
		std::cout << v;
		V.Var = v;
		tmp->value = V;
		if (!Stream.get(v))
			throw std::invalid_argument("Error while entering expression");
		if (v != ' ')
			throw std::invalid_argument("Error while entering expression");
		std::cout << ' ';
	}
	void ReadOper(std::shared_ptr<h_list<base>> tmp, char v, std::stringstream& Stream) {
		VarNum<base> Op;
		Op.IsVar = false;
		Op.IsOp = true;
		std::cout << v;
		Op.Var = v;
		tmp->value = Op;
		if (!Stream.get(v))
			throw std::invalid_argument("Error while entering expression");
		if (v != ' ')
			throw std::invalid_argument("Error while entering expression");
		std::cout << ' ';
	}
	void ReadExprRec(std::shared_ptr<h_list<base>> tmp, std::shared_ptr<h_list<base>> &save, std::stringstream &Stream) {
		int IsO = 0;
		std::cout << '(';
		char c = 0;
		
		while (Stream.get(c))
		{
			if (IsO < 2)
			{
				if (c >= '0' && c <= '9')
				{
					ReadNumberToH_List(tmp, c, Stream);
					tmp->AddNext();
					tmp = tmp->next;
					IsO++;
				}
				else if (c >= 'a' && c <= 'z')
				{
					ReadVar(tmp, c, Stream);
					tmp->AddNext();
					tmp = tmp->next;
					IsO++;
				}
				else if (c == '(')
				{
					if (!Stream.get(c))
						throw std::invalid_argument("Error while entering expression");
					if (c != ' ')
						throw std::invalid_argument("Error while entering expression");
					tmp->value = std::make_shared<h_list<base>>();
					ReadExprRec(std::get<std::shared_ptr<h_list<base>>>(tmp->value),
						std::get<std::shared_ptr<h_list<base>>>(tmp->value), Stream);
					IsO++;
					tmp->AddNext();
					tmp = tmp->next;
				}
				else if (c == ')' && IsO == 1)
				{
					if (!Stream.get(c))
						throw std::invalid_argument("Error while entering expression");
					if (c != ' ')
						throw std::invalid_argument("Error while entering expression");
					IsO++;
					std::cout << "\b \b";
					std::cout << ')';
					std::cout << ' ';
					return;
				}
				else
					throw std::invalid_argument("Error while entering expression");
			}
			else if (IsO == 2)
			{
				if ((c == '+' || c == '-' || c == '*' || c == '/'))
				{
					ReadOper(tmp, c, Stream);
					IsO = 1;
					H_ListToValueOfRoot(tmp, save);
					tmp->AddNext();
					tmp = tmp->next;
				}
				else
					throw std::invalid_argument("Error while entering expression");
			}
		}
		throw std::runtime_error("Error while reading from stream");
	}
	bool ReadVarValue(std::stringstream& Stream) {
		std::cout << '(';
		char k = 0;
		if (!Stream.get(k))
			throw std::invalid_argument("Error while entering expression");
		if (k != '(')
			throw std::invalid_argument("Error while entering expression");
		if (!Stream.get(k))
			throw std::invalid_argument("Error while entering expression");
		if (k != ' ')
			throw std::invalid_argument("Error while entering expression");
		if (!Stream.get(k))
			throw std::invalid_argument("Error while entering expression");
		if (k == ')')
		{
			std::cout << ')';
			return 0;
		}
		else if (k >= 'a' && k <= 'z')
		{
			std::cout << k << ' ';
			char c = 0;
			if (!Stream.get(c))
				throw std::invalid_argument("Error while entering expression");
			if (c != ' ')
				throw std::invalid_argument("Error while entering expression");
			if (!Stream.get(c))
				throw std::invalid_argument("Error while entering expression");
			VarValue[k] = new (base);
			*VarValue[k] = ReadNumber(c, Stream);
			std::cout << ')';
			if (!Stream.get(c))
				throw std::invalid_argument("Error while entering expression");
			if (c != ')')
				throw std::invalid_argument("Error while entering expression");
			if (!Stream.get(c))
				throw std::invalid_argument("Error while entering expression");
			if (c == ' ')
				return 0;
			else if (c == ',')
			{
				std::cout << ',';
				return ReadVarValue(Stream);
			}
		}
		else
			throw std::invalid_argument("Error while entering expression");
		return 0;
	}
	base CalcExprRec(std::shared_ptr<h_list<base>> tmp) {
		base O1, O2, Res = 0;

		if (tmp->next == nullptr && std::holds_alternative<std::shared_ptr<h_list<base>>>(tmp->value) && std::get<std::shared_ptr<h_list<base>>>(tmp->value) == nullptr)
			throw std::invalid_argument("Empty hierarchical list");
		if (tmp->next == nullptr || (tmp->next->next == nullptr && std::holds_alternative<std::shared_ptr<h_list<base>>>(tmp->next->value) && std::get<std::shared_ptr<h_list<base>>>(tmp->next->value) == nullptr))
			if (std::holds_alternative<std::shared_ptr<h_list<base>>>(tmp->value))
				Res = CalcExprRec(std::get<std::shared_ptr<h_list<base>>>(tmp->value));
			else
			{
				VarNum N = std::get<VarNum<base>>(tmp->value);
				if (N.IsVar == 0)
					Res = N.Num;
				else
				{
					if (VarValue[N.Var] == 0)
						throw std::invalid_argument("Uninitialized variable");
					Res = *VarValue[N.Var];
				}
			}
		else
		{
			if (std::holds_alternative<std::shared_ptr<h_list<base>>>(tmp->value))
				O1 = CalcExprRec(std::get<std::shared_ptr<h_list<base>>>(tmp->value));
			else
			{
				VarNum N = std::get<VarNum<base>>(tmp->value);
				if (N.IsVar == 0)
					O1 = N.Num;
				else
				{
					if (VarValue[N.Var] == 0)
						throw std::invalid_argument("Uninitialized variable");
					O1 = *VarValue[N.Var];
				}
			}
			tmp = tmp->next;
			if (std::holds_alternative<std::shared_ptr<h_list<base>>>(tmp->value))
				O2 = CalcExprRec(std::get<std::shared_ptr<h_list<base>>>(tmp->value));
			else
			{
				VarNum N = std::get<VarNum<base>>(tmp->value);
				if (N.IsVar == 0)
					O2 = N.Num;
				else
				{
					if (VarValue[N.Var] == 0)
						throw std::invalid_argument("Uninitialized variable");
					O2 = *VarValue[N.Var];
				}
			}
			tmp = tmp->next;
			VarNum N = std::get<VarNum<base>>(tmp->value);
			switch (N.Var)
			{
			case '+':
				Res = O1 + O2;
				break;
			case '-':
				Res = O1 - O2;
				break;
			case '*':
				Res = O1 * O2;
				break;
			case '/':
				Res = O1 / O2;
				break;
			}
		}
		return Res;
	}
public:
	calk(h_list<base> L) {
		H_List = std::make_shared<h_list<base>>(L);
	}
	void ReadExpr(std::stringstream& Stream) {
		char c = 0;
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression");
		if (c != '(')
			throw std::invalid_argument("Error while entering expression");
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression");
		if (c != ' ')
			throw std::invalid_argument("Error while entering expression");
		ReadExprRec(H_List, H_List, Stream);
		std::cout << ' ';
		ReadVarValue(Stream);
	}
	base CalcExpr(void) {
		return CalcExprRec(H_List);
	}
};

#endif // __CALC
