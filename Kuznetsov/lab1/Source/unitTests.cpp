#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

#define RESFILE "result.txt"

unsigned GLwordsInSeq, GLnumOfSeqs;

std::istream& operator>>(std::istream& in, std::vector<std::string>& seq) {
	for (int i = 0; i < GLwordsInSeq; i++) {
		std::string tmp;
		in >> tmp;
		seq.emplace_back(std::move(tmp));
	}
	char c[1];
	in.getline(c, 1);
	return in;
}

std::istream& operator>>(std::istream& in, std::string& seq) {
	char* str = new char[128];
	in.getline(str, 128);
	seq = std::string(str);
	return in;
}

unsigned fact(int n) {
	unsigned res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}

template <typename T>
std::ostream& operator<<(std::ostream & out, const std::vector<T> & seq) {
	out << *seq.begin();
	for (auto it = seq.begin() + 1; it != seq.end(); it++) {
		out << " " << *it;
	}
	return out;
}

template<typename T>
std::string str(T begin, T end)
{
	std::stringstream ss;
	for (bool first = true; begin != end; begin++)
	{
		if (!first)
			ss << " ";
		ss << *begin;
		first = false;
	}
	return ss.str();
}

int main() {
	//freopen(RESFILE, "r", stdin);
	std::cin >> GLwordsInSeq;
	GLnumOfSeqs = fact(GLwordsInSeq);
	std::vector<std::string> seq;
	std::cin >> seq;
	std::cout << "Running test [" << seq << "]...\n";
	std::set<std::string> myPermutations, truePermutations;
	myPermutations.insert(str(seq.begin(), seq.end()));
	unsigned permCount = GLnumOfSeqs;
	for (int i = 0; i < permCount - 1; i++) {
		std::string tmp;
		std::cin >> tmp;
		if (myPermutations.count(tmp)) {
			std::cout << "Test failed: your algorithm generated identical permutations\n";
			return 0;
		}
		myPermutations.emplace(std::move(tmp));
	}
    std::sort(seq.begin(), seq.end());
	do {
		truePermutations.insert(str(seq.begin(), seq.end()));
	} while (std::next_permutation(seq.begin(), seq.end()));
	std::vector<std::string> diff;
	std::set_difference(myPermutations.begin(), myPermutations.end(),
		truePermutations.begin(), truePermutations.end(), std::inserter(diff, diff.begin()));
	if (!diff.size() && myPermutations.size() == truePermutations.size()) {
		std::cout << "Test: completed successfully\n";
		return 0;
	}

	std::cout << "your alg ans\n";
	for (auto it = myPermutations.begin(); it != myPermutations.end(); it++)
		std::cout << *it << "\n";
	std::cout << "------------\n";
	std::cout << "true ans\n";
	for (auto it = truePermutations.begin(); it != truePermutations.end(); it++)
		std::cout << *it << "\n";
	std::cout << "------------\n";
	std::cout << "Test [" << seq << "] completed successfully\n\n";
}