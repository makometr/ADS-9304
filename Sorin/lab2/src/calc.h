#ifndef __CALC
#define __CALC

#include "h_list.h"
#include <stdexcept>
#include <conio.h>


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
	base ReadNumber(char k) {
		base Num = 0;

		if (k == '0')
		{
			std::cout << '0';
			k = _getch();
			if (k == ',')
			{
				std::cout << ',';
				int I = 0;
				while (k != 13)
				{
					if (I == 0)
						while (k < '0' || k > '9')
							k = _getch();
					else
						k = _getch();
					if (k >= '0' && k <= '9')
					{
						std::cout << k;
						base deg = 0.1;
						for (int i = 0; i < I; i++)
							deg /= 10;
						Num += deg * ((base)k - '0');
						I++;
					}
				}
			}
			else if (k == '13')
				Num = 0;
			
			return Num;
		}
		while (1)
		{
			if (k >= '0' && k <= '9')
			{
				std::cout << k;
				Num *= 10;
				Num += ((base)k - '0');
				break;
			}
			k = _getch();
		}
		while (k != 13)
		{
			k = _getch();
			if (k >= '0' && k <= '9')
			{
				std::cout << k;
				Num *= 10;
				Num += ((base)k - '0');
			}
			else if (k == ',')
			{
				std::cout << ',';
				int I = 0;
				while (k != 13)
				{
					if (I == 0)
						while (k < '0' || k > '9')
							k = _getch();
					else
						k = _getch();
					if (k >= '0' && k <= '9')
					{
						std::cout << k;
						base deg = 0.1;
						for (int i = 0; i < I; i++)
							deg /= 10;
						Num += deg * ((base)k - '0');
						I++;
					}
				}
			}
		}
		return Num;
	}
	void ReadNumberToH_List(std::shared_ptr<h_list<base>> tmp, char k) {
		VarNum<base> Num;
		Num.IsVar = false;
		Num.IsOp = false;
		Num.Num = ReadNumber(k);
		tmp->value = Num;
		std::cout << ' ';
	}
	void ReadVar(std::shared_ptr<h_list<base>> tmp, char v) {
		VarNum<base> V;
		V.IsVar = true;
		V.IsOp = false;
		std::cout << v;
		V.Var = v;
		tmp->value = V;
		std::cout << ' ';
	}
	void ReadOper(std::shared_ptr<h_list<base>> tmp, char v) {
		VarNum<base> Op;
		Op.IsVar = false;
		Op.IsOp = true;
		std::cout << v;
		Op.Var = v;
		tmp->value = Op;
		std::cout << ' ';
	}
	void ReadExprRec(std::shared_ptr<h_list<base>> tmp, std::shared_ptr<h_list<base>> &save) {
		int IsO = 0;
		std::cout << '(';
		while (1)
		{
			int c = _getch();
			if (IsO < 2)
				while (1)
				{
					if (c >= '0' && c <= '9')
					{
						ReadNumberToH_List(tmp, c);
						tmp->AddNext();
						tmp = tmp->next;
						IsO++;
						break;
					}
					else if (c >= 'a' && c <= 'z')
					{
						ReadVar(tmp, c);
						tmp->AddNext();
						tmp = tmp->next;
						IsO++;
						break;
					}
					else if (c == '(')
					{
						tmp->value = std::make_shared<h_list<base>>();
						ReadExprRec(std::get<std::shared_ptr<h_list<base>>>(tmp->value), std::get<std::shared_ptr<h_list<base>>>(tmp->value));
						IsO++;
						tmp->AddNext();
						tmp = tmp->next;
						break;
					}
					else if (c == ')' && IsO == 1)
					{
							IsO++;
							std::cout << "\b \b";
							std::cout << ')';
							std::cout << ' ';
							return;
					}
					else
						c = _getch();
				}

			//int c = _getch();
			if (IsO == 2)
				while (1)
				{
					if ((c == '+' || c == '-' || c == '*' || c == '/'))
					{
						ReadOper(tmp, c);
						IsO = 1;
						H_ListToValueOfRoot(tmp, save);
						tmp->AddNext();
						tmp = tmp->next;
						break;
					}
					else
						c = _getch();
				}
		}
	}
	bool ReadVarValue() {
		std::cout << '(';
		char k = _getch();
		while (k < 'a' || k > 'z')
		{
			if (k == 13)
			{
				std::cout << ')';
				return 0;
			}
			k = _getch();
		}
		std::cout << k << ' ';
		char c = _getch();
		while (c < '0' || c > '9')
			c = _getch();
		VarValue[k] = new (base);
		*VarValue[k] = ReadNumber(c);
		std::cout << ')';
		k = _getch();
		while (1)
		{
			if (k == 13)
				return 0;
			else if (k == ',')
				return ReadVarValue();
			k = _getch();
		}
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
	void ReadExpr(void) {
		ReadExprRec(H_List, H_List);
		std::cout << '\n';
		ReadVarValue();
	}
	base CalcExpr(void) {
		return CalcExprRec(H_List);
	}
};

#endif // __CALC
