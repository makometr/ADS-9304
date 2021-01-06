#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>

class AVL_Tree;
class TK;
class Node {
public:
	Node(int k): key(k) {
		height = 1;
	}
	Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right, int k) : left(left), right(right), key(k) {
		height = 1;
	}
private:
	friend class AVL_Tree;
	friend class TK;
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;
	int height;
	int key;
};

class AVL_Tree {
public:
	AVL_Tree(std::vector<int> v) {
		std::sort(v.begin(), v.end());
		Head = this->create_AVL(v);
	}
	void print_avl() {
		print_node(this->Head);
	}
	std::shared_ptr<Node> get_head() {
		return this->Head;
	}
	bool search_item(std::shared_ptr<Node> ptr, int k) {
		if (ptr == nullptr) {
			return false;
		}
		else if (ptr->key > k) {
			return search_item(ptr->left, k);
		}
		else if (ptr->key < k) {
			return search_item(ptr->right, k);
		}
		else {
			return true;
		}
	}
	void inserting_elem(int k) {
		if (!search_item(this->Head, k)) {
			insert(this->Head, k);
			//std::cout << "insert\n";
		}
		else {
			//std::cout << "The elem already exists\n";
		}
	}
	void delete_elem(int k) {
		if (search_item(this->Head, k)) {
			Head = remove(this->Head, k);
			//std::cout << "delete\n";
		}
		else {
			//std::cout << "elem not found \n";
		}
	}

private:
	std::shared_ptr<Node> Head;
	void print_node(std::shared_ptr<Node> ptr, int i = 0) {
		if (ptr != nullptr) {
			if (ptr->right) {
				print_node(ptr->right, i + 4);
			}
			if (i) {
				std::cout << std::setw(i) << ' ';
			}
			if (ptr->right) {
				std::cout << " /\n" << std::setw(i) << ' ';
			}
			std::cout << ptr->key <<" " << ptr->height << "\n ";
			if (ptr->left) {
				std::cout << std::setw(i) << ' ' << " \\\n";
				print_node(ptr->left, i + 4);
			}
		}
	}
	std::shared_ptr<Node> create_AVL(std::vector<int> v) {
		if (v.size() == 1) {
			std::shared_ptr<Node> node = std::make_shared<Node>(v[0]);
			node->left = nullptr;
			node->right = nullptr;
			return node;
		}
		else if (v.empty()) {
			return nullptr;
		}
		else {
			size_t i = v.size() / 2;
			std::vector<int> v_left;
			std::vector<int> v_right;
			for (size_t z = 0; z < i; ++z) {
				v_left.push_back(v.at(z));
			}
			for (size_t z = i+1 ; z < v.size(); ++z) {
				v_right.push_back(v.at(z));
			}
			std::shared_ptr<Node> node = std::make_shared<Node>(v[i]);
			node->left = create_AVL(v_left);
			node->right = create_AVL(v_right);
			fixheight(node);
			return node;
		}
	}
	int bfactor(std::shared_ptr<Node> p)
	{	
		int lHeight = 0, rHeight = 0;
		if (p->left != nullptr) {
			lHeight = p->left->height;
		}
		if (p->right != nullptr) {
			rHeight = p->right->height;
		}
		return ( rHeight - lHeight);
	}

	void fixheight(std::shared_ptr<Node> ptr)
	{
		if (ptr->left) {
			fixheight(ptr->left);
		}
		if (ptr->right) {
			fixheight(ptr->right);
		}
		if (ptr->left == nullptr && ptr->right == nullptr) {
			ptr->height = 1;
		}
		else if (ptr->right == nullptr) {
			ptr->height = (ptr->left->height + 1);
		}
		else if (ptr->left == nullptr) {
			ptr->height = (ptr->right->height + 1);
		}
		else {
			ptr->height = ptr->left->height > ptr->right->height ? ptr->left->height : ptr->right->height;
			ptr->height++;
		}
		
	}
	std::shared_ptr<Node> rotateright(std::shared_ptr<Node> p) // правый поворот вокруг p
	{
		std::shared_ptr<Node> q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	std::shared_ptr<Node> rotateleft(std::shared_ptr<Node> q) // левый поворт вокруг q
	{
		std::shared_ptr<Node> p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	std::shared_ptr<Node> balance(std::shared_ptr<Node> ptr) // балансировка узла ptr
	{
		fixheight(ptr);
		if (bfactor(ptr) == 2)
		{
			if (bfactor(ptr->right) < 0)
				ptr->right = rotateright(ptr->right);
			return rotateleft(ptr);
			
		}
		if (bfactor(ptr) == -2)
		{
			if (bfactor(ptr->left) > 0)
				ptr->left = rotateleft(ptr->left);
			return rotateright(ptr);
		}
		return ptr;
	}

	std::shared_ptr<Node> insert(std::shared_ptr<Node> p, int k) // вставка ключа k в дерево с корнем p
	{
		if (p == nullptr) 
			return std::make_shared<Node>(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}
	std::shared_ptr<Node> findmin(std::shared_ptr<Node> ptr) {
		if(ptr == nullptr) {
			return nullptr;
		}
		return ptr->left ? findmin(ptr->left) : ptr;
	}
	std::shared_ptr<Node> removemin(std::shared_ptr<Node> p){// удаление узла с минимальным ключом из дерева p
		if (!p) {
			return nullptr;
		}
		else if (!p->left) {
			return p->right;
		}
		else {
			p->left = removemin(p->left);// , min);
			return balance(p);
		}
	}

	std::shared_ptr<Node> remove(std::shared_ptr<Node> p, int k) // удаление k из дерева p
	{
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			if (p->right == nullptr) {
				return p->left;
			}
			auto min = findmin(p->right);
			min->right = removemin(p->right);
			min->left = p->left;
			return balance(min);
		}
		return balance(p);
	}

};


class TK {
public:
	TK() {
		teacher.open("Teacher.txt");
		student.open("Student.txt");
	}
	~TK() {
		teacher.close();
		student.close();
	}
	void start_TR() {
		std::string q_task_ = "Здравствуйте! Сколько заданий вы хотите сгенерировать? ";
		std::string type_task_ = "Выберите тип задания:\n1) Вставка\n2) Удаление\n3) Удаление и вставка\nВведите цифпу соотвествющую типу задания: ";
		std::string q_elem_in_tree_ = "Введите количество элементов в дереве: ";
		std::string delete_str = " Удалите из дерева следующий элемент: \n";
		std::string insert_str = " Вставьте в дерево следующий элемент: \n";
		unsigned int q_task;
		unsigned int type_task;
		unsigned int q_elem_in_tree;
		std::cout << q_task_;
		std::cin >> q_task;
		std::cout << type_task_;
		std::cin >> type_task;
		std::cout << q_elem_in_tree_;
		std::cin >> q_elem_in_tree;
		if (q_task == 0) {
			std::cout << "Количество заданий должно быть больше 0";
		}
		else if (type_task != 3 && type_task != 1 && type_task != 2 ) {
			std::cout << "Неопределенный тип задания";
		}
		else {
			
			
			for (unsigned int i = 1; i <= q_task; ++i) {
				std::vector<int> Avl;
				for (unsigned int i = 0; i < q_elem_in_tree;) {
					int x;
					if (count(Avl.begin(), Avl.end(), x = rand()) == 0) {
						Avl.push_back(x);
						++i;
					}
				}
				tree = std::make_shared<AVL_Tree>(Avl);
				if (type_task == 1 || (type_task == 3 && i%2 ==0)) {
					teacher << "Задание №" << i << insert_str;
					student << "Задание №" << i << insert_str;
					create_task_insert(Avl);
					
				}
				else if (type_task == 2 || (type_task == 3 && i % 2 == 1)) {
					teacher << "Задание №" << i << delete_str;
					student << "Задание №" << i << delete_str;
					create_task_delete(Avl);
				}
				Avl.clear();
			}
			
		}

	}
private:
	std::shared_ptr<AVL_Tree> tree;
	std::ofstream teacher;
	std::ofstream student;
	void create_task_delete(std::vector<int>& v) {
		int k = (rand() % v.size());
		teacher << v[k] << "\n";
		student << v[k] << "\n";
		this->print_avl_student(this->tree->get_head());
		this->print_avl_teacher(this->tree->get_head());
		this->tree->delete_elem(v[k]);
		teacher << "\nОтвет:\n";
		this->print_avl_teacher(this->tree->get_head());
	}
	void create_task_insert(std::vector<int>& v) {
		int x;
		do {
			x = rand();
		} while(count(v.begin(), v.end(), x) != 0);
		teacher << x << "\n";
		student << x << "\n";
		this->print_avl_student(this->tree->get_head());
		this->print_avl_teacher(this->tree->get_head());
		this->tree->inserting_elem(x);
		teacher << "\nОтвет:\n";
		this->print_avl_teacher(this->tree->get_head());
		
	}
	void print_avl_teacher(std::shared_ptr<Node> ptr, int i = 0) {
		if (ptr != nullptr) {
			if (ptr->right) {
				print_avl_teacher(ptr->right, i + 4);
			}
			if (i) {
				teacher << std::setw(i) << ' ';
			}
			if (ptr->right) {
				teacher << " /\n" << std::setw(i) << ' ';
			}
			teacher << ptr->key << "\n ";
			if (ptr->left) {
				teacher << std::setw(i) << ' ' << " \\\n";
				print_avl_teacher(ptr->left, i + 4);
			}
		}
	}
	void print_avl_student(std::shared_ptr<Node> ptr, int i = 0) {
		if (ptr != nullptr) {
			if (ptr->right) {
				print_avl_student(ptr->right, i + 4);
			}
			if (i) {
				student << std::setw(i) << ' ';
			}
			if (ptr->right) {
				student << " /\n" << std::setw(i) << ' ';
			}
			student << ptr->key << "\n ";
			if (ptr->left) {
				student << std::setw(i) << ' ' << " \\\n";
				print_avl_student(ptr->left, i + 4);
			}
		}
	}
};


int main() {
	setlocale(LC_ALL, "Russian");
	TK task;
	task.start_TR();
	return 0; 
}