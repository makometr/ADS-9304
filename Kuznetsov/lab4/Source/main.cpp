#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>
#include <iterator>
#include <mutex>
#ifdef  _DEBUG
std::mutex cerr_mutex; //Sorry, i have to...
#endif
template <typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& seq) {
	seq.reserve(8);
	while (in.peek() != '\n' && in.peek() != EOF)
	{
		T tmp;
		in >> tmp;
		seq.push_back(tmp);
	}
	return in;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T>& seq) {
	std::copy(seq.begin(), seq.end(), std::ostream_iterator<T>(out, " "));
	return out << '\n';
}
namespace bitSort {
	enum direction {
		ASCENDING, //0
		DESCENDING, //1
	};
	template <typename T>
	void makeBitonic(std::vector<T>& seq, const unsigned begin, const unsigned compDist, const direction dir) {
#ifdef _DEBUG
		{const std::lock_guard <std::mutex> lock_cerr(cerr_mutex);
		std::cerr << "\033[35m[Making]\033[m BS size \033[33m" << 2 * compDist << "\033[m; Comparation distance: \033[33m"
				<< compDist << "\033[m; dir = " << (dir ? "\033[31mDESCENDING" : "\033[32mASCENDING") << "\033[m\n";}
#endif
		for (unsigned i = begin; i < seq.size(); i += 4 * compDist)
			for (unsigned j = i; j < i + compDist; j++)
				if ((seq[j] > seq[j + compDist]) != dir)
					std::swap(seq[j + compDist], seq[j]);
	}
	template <typename T>
	void mergeBitonic(std::vector<T> & seq, const unsigned begin, const unsigned length, const unsigned compDist, const direction dir) {
#ifdef _DEBUG
		{const std::lock_guard <std::mutex> lock_cerr(cerr_mutex);
		std::cerr << "\033[34m[Merging]\033[m BS size \033[33m" << length << "\033[m; Comparation distance: \033[33m"
				<< compDist << "\033[m; dir = " << (dir ? "\033[31mDESCENDING" : "\033[32mASCENDING") << "\033[m\n"; }
#endif
		for (unsigned i = begin; i < seq.size(); i += 2 * length) 
			for (unsigned j = i; j < i + length; j += 2 * compDist)
				for (unsigned k = j; k < j + compDist; k++)
					if ((seq[k] > seq[k + compDist]) != dir)
						std::swap(seq[k + compDist], seq[k]);
	}
	template <typename T>
	void debug_print(std::ostream& out, const std::vector<T>& seq, const unsigned bsSize) {
#ifdef _DEBUG
		if (!bsSize) {
			std::copy(seq.begin(), seq.end(), std::ostream_iterator<T>(out, " "));
			out << '\n';
			return;
		}
		char color[][6] = { "\033[32m", "\033[31m" };
		bool pick = 0;
		for (auto it = seq.begin(); it != seq.end(); it+=bsSize) {
			out << color[pick];
			pick = !pick;
			for (auto jt = it; std::distance(it, jt) < bsSize; jt++)
				out << *jt << ' ';
		}
		out << "\033[m\n";
#endif
	}
};
template <typename T>
void bitonicSort(std::vector<T>& seq) {
	size_t oldSize = seq.size(),
		newSize = 1 << static_cast<size_t>(std::ceil(std::log2(seq.size())));
	seq.resize(newSize, *std::max_element(seq.begin(), seq.end())); //bitonic sort only works with sequences of 2^x length
	for (size_t i = 2; i < newSize; i *= 2) { // i = Bitonic Sequence size
		std::thread makeAscending(bitSort::makeBitonic<T>, std::ref(seq), 0, i / 2, bitSort::ASCENDING);
		bitSort::makeBitonic<T>(seq, i, i / 2, bitSort::DESCENDING);
		makeAscending.join();
		for (size_t j = i / 4; j > 0; j /= 2) { //merging
			std::thread mergeAscending(bitSort::mergeBitonic<T>, std::ref(seq), 0, i, j, bitSort::ASCENDING);
			bitSort::mergeBitonic<T>(seq, i, i, j, bitSort::DESCENDING);
			mergeAscending.join();
			if(j>1)
				bitSort::debug_print(std::cerr, seq, 0);
		}
		bitSort::debug_print(std::cerr, seq, i);
	}
	for (int j = newSize / 2; j > 0; j /= 2) { //final merge
		bitSort::mergeBitonic(seq, 0, newSize, j, bitSort::ASCENDING);
		bitSort::debug_print(std::cerr, seq, 0);
	}
	seq.resize(oldSize); //remove fictitious elements
}
int main() {
	std::vector<int> seq;
#ifndef TEST
	std::cout << "Enter a sequence: ";
#endif
	std::cin >> seq;
#ifdef _DEBUG
	std::vector<int>test = seq;
#endif
	bitonicSort(seq);
#ifndef TEST
	std::cout << "Sorted sequence: ";
#endif
	std::cout << seq;
#ifdef _DEBUG
	std::sort(test.begin(), test.end());
	if (std::equal(seq.begin(), seq.end(), test.begin(), test.end()))
		std::cerr << "\033[32mSorted sequence validated successfully\033[m\n";
	else
		std::cerr << "\033[31mERROR: sequence wasn't sorted correctly\033[m\n";
		
#endif
	return 0;
}