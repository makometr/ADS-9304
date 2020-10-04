#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream & out, const std::vector<T> & seq) {
	out << *seq.begin();
	for (auto it = seq.begin() + 1; it != seq.end(); it++) {
		out << " " << *it;
	}
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
	std::vector<std::string> seq;
	std::cin >> seq;
	std::cout<<seq.size()<<"\n";
	auto permutationGen = [&seq](std::vector<std::string>::iterator begin, auto && permutationGen) {
		//printing
		if (begin == seq.end()) {
			std::cout << seq << '\n';
			return;
		}
		//recource block
		for (auto i = begin; i != seq.end(); i++) {
			std::swap(*begin, *i);
			permutationGen(begin + 1, permutationGen);
			std::swap(*begin, *i);
		}
	};

	permutationGen(seq.begin(), permutationGen);
	return 0;
}