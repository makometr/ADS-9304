#include "Recursion.h"

bool Recursion::IsBrackets(string& str, int position, int deep)
{
	bool ans = false;
	size_t found = 0;
	size_t found2 = 0;

	if (str.length() == 1 && str[position] == 'A'){
		ans = true;
	}

	else if (str.length() != 0) {
		switch (str[position])
		{
		case '(':

			if (str[position + 1] == ')' || str[position + 1] == '(' || str[position + 1] == 'A') {
				ans = false;
			}
			else {
				ans = this->IsBrackets(str, position + 1, ++deep);
			}
			break;

		case 'A':
			if (str[position + 1] == '\0') {
				ans = true;
			}
			else if (str[position + 1] == 'B' || str[position + 1] == '(' || str[position + 1] == 'A') {
				ans = false;
			}
			else {
				ans = this->IsBrackets(str, position + 1, ++deep);
			}
			break;

		case 'B':
			if (str[position + 1] == 'B' || str[position + 1] == ')' || position == 0) {
				ans = false;
			}
			else {
				ans = this->IsBrackets(str, position + 1, ++deep);
			}
			break;

		case ')':
			if (str[position + 1] == 'B' || str[position + 1] == ')') {
				ans = false;
			}
			else {
				ans = this->IsBrackets(str, position + 1, ++deep);
			}
			break;

		default:
			ans = false;
			break;
		}
	}

	return ans;
}

