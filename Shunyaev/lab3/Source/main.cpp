#include <memory>
#include <string>
#include <math.h>
#include "TreeElement.h"
#include "InputData.h"

template <typename T1>
class BTree
{
public:
	int tree_size = 0;
	std::unique_ptr<TreeElement<T1>[]> tree;

	BTree(std::string& str);
	~BTree();

	void Print(int tab, int iter, std::ofstream& file);
	void PrintTest(int iter, std::ofstream& test_file);
	void Simplify();
	void TreeInit(std::string& str, int tree_iter, int& str_iter);

	

};

template<typename T1>
BTree<T1>::BTree(std::string& str)
{	
	int tree_iter = 0;
	int str_iter = str.length() - 1;
	int temp = 0;

	this->tree_size = 16;
	this->tree = std::make_unique<TreeElement<T1>[]>(this->tree_size);
	
	this->TreeInit(str, tree_iter, str_iter);
}

template<typename T1>
BTree<T1>::~BTree()
{
}

template<typename T1>
void BTree<T1>::Print(int tab, int iter, std::ofstream& file)
{
	int temp = tab;
	std::string str = "";
	while (temp != 0) {
		str += "  ";
		temp--;
	}
	if (tree[iter].is_set) {
		if (std::holds_alternative<T1>(this->tree[iter].data_)) {
			if (std::get<T1>(this->tree[iter].data_) < 0) {
				file << str << "0 - " << abs(std::get<T1>(this->tree[iter].data_)) << '\n';
			}
			else {
				file << str << std::get<T1>(this->tree[iter].data_) << '\n';
			}
			
		}
		else {
			file << str << std::get<char>(this->tree[iter].data_) << '\n';

			if (std::get<char>(this->tree[iter].data_) == '+' || std::get<char>(this->tree[iter].data_) == '-' ||
				std::get<char>(this->tree[iter].data_) == '*' || std::get<char>(this->tree[iter].data_) == '/')
			{
				this->Print(tab + 1, (2 * iter) + 1, file);
				this->Print(tab + 1, (2 * iter) + 2, file);
			}
		}
	}
}

template<typename T1>
void BTree<T1>::PrintTest(int iter, std::ofstream& test_file)
{
	if (tree[iter].is_set) {
		if (std::holds_alternative<T1>(this->tree[iter].data_)) {
			if (std::get<T1>(this->tree[iter].data_) < 0) {
				test_file << " 0 - " << abs(std::get<T1>(this->tree[iter].data_)) << ' ';
			}
			else {
				test_file << std::get<T1>(this->tree[iter].data_) << ' ';
			}

		}
		else {
			//file << str << std::get<char>(this->tree[iter].data_) << '\n';

			if (std::get<char>(this->tree[iter].data_) == '+' || std::get<char>(this->tree[iter].data_) == '-' ||
				std::get<char>(this->tree[iter].data_) == '*' || std::get<char>(this->tree[iter].data_) == '/')
			{
				test_file << "( ";
				this->PrintTest((2 * iter) + 1, test_file);
				test_file << std::get<char>(this->tree[iter].data_) << ' ';
				this->PrintTest((2 * iter) + 2, test_file);
				test_file << ") ";
			}
			else {
				test_file << std::get<char>(this->tree[iter].data_) << ' ';
			}
		}
	}
}

template<typename T1>
void BTree<T1>::Simplify()
{
	for (int i = this->tree_size - 1; i >= 0; --i) {
		if (tree[i].is_set) {
			if (std::holds_alternative<char>(this->tree[i].data_) && std::get<char>(this->tree[i].data_) == '-')
			{
				if (std::holds_alternative<T1>(this->tree[(2 * i) + 1].data_)
					&& std::holds_alternative<T1>(this->tree[(2 * i) + 2].data_))
				{
					tree[i].data_ = std::get<T1>(this->tree[(2 * i) + 1].data_) - std::get<T1>(this->tree[(2 * i) + 2].data_);
					tree[(2 * i) + 1].is_set = false;
					tree[(2 * i) + 2].is_set = false;
				}
			}
		}
	}
}

template<typename T1>
void BTree<T1>::TreeInit(std::string& str, int tree_iter, int& str_iter)
{
	if (tree_iter >= this->tree_size - 2) {

		int new_size = tree_size * 2;
		std::unique_ptr<TreeElement<T1>[]> temp = std::make_unique<TreeElement<T1>[]>(new_size);

		for (int i = 0; i < tree_size; i++) {
			temp[i] = tree[i];
		}

		this->tree = std::move(temp);
		this->tree_size = new_size;
	}
	bool right_side = true;
	for (str_iter; str_iter >= 0; --str_iter)
	{
		if (str[str_iter] == '+' || str[str_iter] == '-' || str[str_iter] == '*' || str[str_iter] == '/')
		{
			if (str_iter == str.length() - 1) {
				tree[tree_iter].data_ = str[str_iter];
				tree[tree_iter].is_set = true;
			}
			else {
				if (right_side) {
					tree[(2 * tree_iter) + 2].data_ = str[str_iter];
					tree[(2 * tree_iter) + 2].is_set = true;
					this->TreeInit(str, 2 * (tree_iter)+2, --str_iter);
					right_side = false;
				}
				else {
					tree[(2 * tree_iter) + 1].data_ = str[str_iter];
					tree[(2 * tree_iter) + 1].is_set = true;
					this->TreeInit(str, 2 * (tree_iter)+1, --str_iter);
					right_side = true;
				}
				if (right_side) {
					return;
				}
			}
		}
		else {
			if ((str[str_iter] >= 'a' && str[str_iter] <= 'z') || (str[str_iter] >= '0' && str[str_iter] <= '9'))
			{
				if (right_side) {
					if ((str[str_iter] >= '0' && str[str_iter] <= '9')) {
						char s = str[str_iter];
						T1 temp = std::atoi(&s);
						tree[(2 * tree_iter) + 2].data_ = temp;
						tree[(2 * tree_iter) + 2].is_set = true;
						right_side = false;
					}
					else {
						tree[(2 * tree_iter) + 2].data_ = str[str_iter];
						tree[(2 * tree_iter) + 2].is_set = true;
						right_side = false;
					}
				}
				else {
					if ((str[str_iter] >= '0' && str[str_iter] <= '9')) {
						char s = str[str_iter];
						T1 temp = std::atoi(&s);
						tree[(2 * tree_iter) + 1].data_ = temp;
						tree[(2 * tree_iter) + 1].is_set = true;
						right_side = true;
					}
					else {
						tree[(2 * tree_iter) + 1].data_ = str[str_iter];
						tree[(2 * tree_iter) + 1].is_set = true;
						right_side = true;
					}
				}

				if (right_side) {
					return;
				}
			}
		}
	}
}

int main() {
	InputData data;
	std::ofstream file("./Tests/output.txt");
	std::ofstream test_file("./Tests/output_test.txt");
	int iter = 1;


	while (data.list.size() != 0)
	{
		BTree<int> b_tree(data.list.front());

		file << "\n\n -----------< Tree #" << iter << " >----------- \n\n";
		test_file << "\n\n -----------< Tree #" << iter << " >----------- \n\n";

		b_tree.Print(0,0, file);
		b_tree.PrintTest(0, test_file);

		b_tree.Simplify();

		file << "\n\n -----------< Simplified Tree #" << iter << " >----------- \n\n";
		test_file << "\n\n -----------< Simplified Tree #" << iter << " >----------- \n\n";

		b_tree.Print(0,0, file);
		b_tree.PrintTest(0, test_file);

		data.list.pop_front();
		iter++;
	}

	test_file.close();
	file.close();
	return 0;
}


