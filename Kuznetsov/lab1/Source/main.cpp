#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& seq) {
	for (const auto& i : seq)
		out << i << " ";
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& seq) {
	while (std::cin.peek() != '\n')
	{
		std::string tmp;
		in >> tmp;
		seq.emplace_back(std::move(tmp));
	}
	return in;
}

int main() {
	std::cout<<"Enter a sequence of words/numbers separated by a space\n";
	std::vector<std::string> seq;
	std::cin >> seq;
	std::sort(seq.begin(), seq.end());
	std::cout << "-------------------\n";

	auto nextPermutation = [&seq](std::vector<std::string>::iterator begin, auto && nextPermutation) {
		//printing
		if (begin == seq.end()) {
			std::cout << seq << '\n';
			return;
		}

		//recource block
		for (auto i = begin; i != seq.end(); i++) {
			std::swap(*begin, *i);
			nextPermutation(begin + 1, nextPermutation);
			std::swap(*begin, *i);
		}
	};

	nextPermutation(seq.begin(), nextPermutation);
	std::system("pause");
	return 0;
}