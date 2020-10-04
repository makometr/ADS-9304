#include <string>
#include <iostream>
#include <vector>
#include <sstream>
 
using namespace std;
 
void isOperationCorrect(int& i, int& result, vector<string> vec) {
	if (vec[i] == "AND") {
		++i;
		result += 0;
	}
	else if (vec[i] == "OR") {
		++i;
		result += 0;
	}
	else {
		result += 1;
	}
}
int main(int argc, char *argv[]) {
	string str;
	vector<string> vec;
	int result = 0;
	string value;
	int i = 0;
	int counfOfRepition = 0;
	auto isSimpleLOgicCorrect = [&vec, &result](int& i, auto&& isSimpleLOgicCorrect)->void {
		if (vec[i][0] == '(') {
			vec[i] = vec[i].substr(1);
			vec[vec.size() - 1] = vec[vec.size() - 1].erase(vec[vec.size() - 1].size() - 1);
			if (i  <= vec.size() - 1) {
				isSimpleLOgicCorrect(i, isSimpleLOgicCorrect);
				if (i  <= vec.size() - 1) {
					isOperationCorrect(i, result, vec);
					if (i  <= vec.size() - 1) {
						isSimpleLOgicCorrect(i, isSimpleLOgicCorrect);
					}
					else { 
						result += 1;
					}
				}
				else {
					result += 1;
				}
			}
			else {
				result += 1;
			}
 
		}
		else if (vec[i] == "TRUE") {
			++i;
			result += 0;
		}
		else if (vec[i] == "FALSE") {
			++i;
			result += 0;
		}
		else if (vec[i].size() == 1 && isupper(vec[i][0])) {
			++i;
			result += 0;
		}
		else if (vec[i] == "NOT") {
			if (i + 1 <= vec.size()-1) {
				++i;
				isSimpleLOgicCorrect(i, isSimpleLOgicCorrect);
			}
			else {
				result += 1;
			}
			result += 0;
		}
		else {
			result += 1;
		}
	};
	if(argc < 2){
                getline(cin, str, '\n');
        }else{
                for(int j = 1; argv[j]; j++){
                        for(int k = 0; argv[j][k]; k++){
                                str.push_back(argv[j][k]);
                        }
                        if(argv[j+1]){
                                str.push_back(' ');
                        }
                }
        }
 
	std::stringstream ss(str);
 
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			counfOfRepition++;
		}
	}
	while (ss >> value)
	{
		vec.push_back(value);
 
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}
 
	if (counfOfRepition != vec.size() - 1) {
		result += 1;
	}
 
 
	isSimpleLOgicCorrect(i, isSimpleLOgicCorrect);
 
	if (i != vec.size()) {
		result += 1;
	}
	str.clear();
 
	if (!result) {
		cout << "The string is correct" << '\n';
	}
	else {
		cout << "The string is not correct" << '\n';
	}
 
}
