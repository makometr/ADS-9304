#include <chrono>
#include <random>

#include "treap.h"

template <typename T>
Treap<T>::Treap(std::shared_ptr<Node<T>> head) : head_(head) {}

template <typename T>
Treap<T>& Treap<T>::operator=(Node<T>& tree) {
  if (this->head_ == &tree) {
    return *this;
  }
  head_ = tree;
  return *this;
}

template <typename T>
void Treap<T>::Insert(const T& data) {
  PrintSeparator();
  std::cout << Color::kPurple << "Начало вставки\n" << Color::kDefault;
  PrintSeparator();
  // std::random_device rd;
  // std::mt19937 mersenne_twister(rd());
  srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::shared_ptr<Node<T>> elem(new Node<T>(data, rand()));
  head_ = InsertPrivate(head_, elem);

  PrintSeparator();
  std::cout << Color::kPurple
            << "Конец вставки\nДерамида после вставки:" << Color::kDefault;
  std::cout << Color::kGreen << '\n';
  PrintAndPaintFullBinaryTree(head_, Color::kGreen, Color::kGreen);
  std::cout << Color::kDefault;
  PrintSeparator();

  PrintSeparator(Color::kDefault, 12, '\n');
}

template <typename T>
void Treap<T>::Remove(const T& data) {
  PrintSeparator();
  std::cout << Color::kPurple << "Начало удаления\n" << Color::kDefault;
  PrintSeparator();

  RemovePrivate(head_, data);

  PrintSeparator();
  std::cout << Color::kPurple
            << "Конец удаления\nДерамида после удаления:" << Color::kDefault;
  std::cout << Color::kGreen << '\n';
  PrintAndPaintFullBinaryTree(head_, Color::kGreen, Color::kGreen);
  std::cout << Color::kDefault;
  PrintSeparator();

  std::cout << "\n\n\n\n";  // FIXIT
}

template <typename T>
size_t Treap<T>::Count(const T& data) const {
  return RecursiveCount(head_, data);
}

template <typename T>
size_t Treap<T>::GetHeight() const {
  return GetHeightPrivate(head_);
}

template <typename T>
size_t Treap<T>::CountAndThenInsert(const T& data) {
  size_t save_count = Count(data);
  Insert(data);
  return save_count;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Treap<T>& tree) {
  auto vec = tree.DumpFullBinaryTree();
  tree.PrintFullBinaryTree(out, vec);
  return out;
}

template <typename T>
std::shared_ptr<Node<T>> Treap<T>::InsertPrivate(
    std::shared_ptr<Node<T>> tree, std::shared_ptr<Node<T>> elem) {
  std::cout << "Вставляемый элемент:";
  PrintDataAndPriority(Color::kGreen, elem);
  std::cout << "\nРассматриваемый элемент (" << Color::kRed << "T"
            << Color::kDefault << ") дерева:";
  PrintDataAndPriority(Color::kGreen, tree);
  std::cout << '\n' << "Текущее дерево:\n";
  if (!tree) {
    std::cout << " #";
  }

  std::shared_ptr<Node<T>> new_element(nullptr);
  if (tree == nullptr) {
    std::cout << "\n\nВставка элемента в пустую область\n";
    new_element = elem;

  } else if (elem->priority_ > tree->priority_) {
    PrintAndPaintFullBinaryTree(tree, Color::kRed);
    std::cout << "\nПриоритет вставляемого элемента оказался" << Color::kRed
              << " больше" << Color::kDefault
              << ", чем приоритет рассматриваемого элемента дерева\n";
    std::cout << "Вставка элемента на место рассматриваемого элемента дерева\n";

    std::cout << Color::kWave << "\nРазделение дерева (" << Color::kRed << "T"
              << Color::kWave << ") на два поддерева (" << Color::kRed << "T1"
              << Color::kWave << " и " << Color::kRed << "T2" << Color::kWave
              << ") так, что в" << Color::kRed << " T1 " << Color::kWave
              << "будет находиться элементы, данные которых" << Color::kRed
              << " меньше " << Color::kWave
              << "данных вставляемого элемента, а в" << Color::kRed << " T2 "
              << Color::kWave << "— все остальные:\n"
              << Color::kDefault;

    new_element = Split(tree, elem->data_);

    std::cout << Color::kWave << "Левое поддерево (" << Color::kRed << "T1"
              << Color::kWave << "):\n"
              << Color::kDefault;
    Treap temp(new_element->left_);
    std::cout << temp << '\n';
    std::cout << Color::kWave << "Правое поддерево (" << Color::kRed << "T2"
              << Color::kWave << "):\n"
              << Color::kDefault;
    temp = new_element->right_;
    std::cout << temp << '\n';

    elem->left_ = new_element->left_;
    elem->right_ = new_element->right_;
    new_element = elem;

    std::cout << Color::kWave << "Подвязываем к вставляемому элементу"
              << Color::kRed << " T1 " << Color::kWave << "левым потомком, а"
              << Color::kRed << " T2 " << Color::kWave
              << "— правым. Вместо рассматриваемого элемента" << Color::kRed
              << " T " << Color::kWave
              << "дерева добавляем вставляемый элемент:\n"
              << Color::kDefault;
    temp = new_element;
    std::cout << temp << '\n';

  } else {
    PrintAndPaintFullBinaryTree(tree, Color::kRed, Color::kGreen);

    std::cout << "\nПриоритет вставляемого элемента оказался" << Color::kRed
              << " не больше" << Color::kDefault
              << ", чем приоритет рассматриваемого элемента дерева\n";

    if (elem->data_ < tree->data_) {
      std::cout << "Переход в" << Color::kRed << " левое " << Color::kDefault
                << "поддерево, так как данные вставляемого элемента оказались"
                << Color::kRed << " меньше" << Color::kDefault
                << ", чем данные рассматриваемого элемента дерева\n";
      PrintSeparator(Color::kBlue);
      tree->left_ = InsertPrivate(tree->left_, elem);
    } else {
      std::cout << "Переход в" << Color::kRed << " правое " << Color::kDefault
                << "поддерево, так как данные вставляемого элемента оказались"
                << Color::kRed << " не меньше" << Color::kDefault
                << ", чем данные рассматриваемого элемента дерева\n";
      PrintSeparator(Color::kBlue);
      tree->right_ = InsertPrivate(tree->right_, elem);
    }
    new_element = tree;
  }
  return new_element;
}

template <typename T>
void Treap<T>::RemovePrivate(std::shared_ptr<Node<T>> tree, const T& data) {
  PrintRemoveInfo(data);
  PrintDataAndPriority(Color::kGreen, tree);
  std::cout << '\n' << "Текущее дерево:\n";
  if (!tree) {
    std::cout << " #";
  } else {
    PrintAndPaintFullBinaryTree(tree, Color::kRed, Color::kGreen);
  }
  std::cout << '\n';

  if (tree == nullptr) {
    std::cout << "Элемент не найден. Попытка удаления из пустой области, "
                 "удаление игнорируется\n";
    return;
  } else if (tree->data_ != data) {
    if (data < tree->data_) {
      std::cout << "Данные удаляемого элемента" << Color::kRed << " меньше"
                << Color::kDefault
                << ", чем данные рассматриваемого элемента дерева. Попытка "
                   "поиска элемента в левом поддереве\n";
      PrintSeparator(Color::kBlue);
      if (tree->left_ != nullptr) {
        if (tree->left_->data_ != data) {
          RemovePrivate(tree->left_, data);
        } else {
          PrintRemoveInfo(data);
          PrintDataAndPriority(Color::kGreen, tree->left_);
          std::cout << '\n' << "Текущее дерево:\n";
          PrintAndPaintFullBinaryTree(tree->left_, Color::kRed, Color::kGreen);
          std::cout << '\n';

          PrintRemoveIfEqual(tree->left_);

          tree->left_ = Merge(tree->left_->left_, tree->left_->right_);

          PrintMerge(tree->left_);
        }
      } else {
        std::cout << "Элемент не найден. Попытка удаления из пустой области, "
                     "удаление игнорируется\n";
      }

    } else {
      std::cout << "Данные удаляемого элемента" << Color::kRed << " не меньше"
                << Color::kDefault
                << ", чем данные рассматриваемого элемента дерева. Попытка "
                   "поиска элемента в правом поддереве\n";
      PrintSeparator(Color::kBlue);
      if (tree->right_ != nullptr) {
        if (tree->right_->data_ != data) {
          RemovePrivate(tree->right_, data);
        } else {
          PrintRemoveInfo(data);
          PrintDataAndPriority(Color::kGreen, tree->right_);
          std::cout << '\n' << "Текущее дерево:\n";
          PrintAndPaintFullBinaryTree(tree->right_, Color::kRed, Color::kGreen);
          std::cout << '\n';

          PrintRemoveIfEqual(tree->right_);

          tree->right_ = Merge(tree->right_->left_, tree->right_->right_);

          PrintMerge(tree->right_);
        }
      } else {
        std::cout << "Элемент не найден. Попытка удаления из пустой области, "
                     "удаление игнорируется\n";
      }
    }
  } else {
    PrintRemoveIfEqual(head_);
    head_ = Merge(head_->left_, head_->right_);
    PrintMerge(head_);
  }
}

template <typename T>
std::shared_ptr<Node<T>> Treap<T>::Split(std::shared_ptr<Node<T>> tree,
                                         const T& data) {
  std::shared_ptr<Node<T>> new_element(nullptr);
  if (tree == nullptr) {
    new_element.reset(new Node<T>(nullptr, nullptr));
  } else if (data > tree->data_) {
    new_element = Split(tree->right_, data);
    tree->right_ = new_element->left_;
    new_element->left_ = tree;
  } else {
    new_element = Split(tree->left_, data);
    tree->left_ = new_element->right_;
    new_element->right_ = tree;
  }
  return new_element;
}

template <typename T>
std::shared_ptr<Node<T>> Treap<T>::Merge(std::shared_ptr<Node<T>> left,
                                         std::shared_ptr<Node<T>> right) {
  std::shared_ptr<Node<T>> new_element(nullptr);
  if (left == nullptr) {
    new_element = right;
  } else if (right == nullptr) {
    new_element = left;
  } else if (left->priority_ > right->priority_) {
    left->right_ = Merge(left->right_, right);
    new_element = left;
  } else {
    right->left_ = Merge(left, right->left_);
    new_element = right;
  }
  return new_element;
}

template <typename T>
size_t Treap<T>::GetHeightPrivate(const std::shared_ptr<Node<T>> tree) const {
  if (tree == nullptr) {
    return 0;
  }
  return 1 + std::max(GetHeightPrivate(tree->left_),
                      GetHeightPrivate(tree->right_));
}

template <typename T>
std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>>
Treap<T>::DumpFullBinaryTree() const {
  std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> vec(GetHeight());
  RecursiveDumpFullBinaryTree(vec, head_);
  return vec;
}

template <typename T>
void Treap<T>::RecursiveDumpFullBinaryTree(
    std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>>& vec,
    std::shared_ptr<Node<T>> elem, long long current_level) const {
  if (current_level == vec.size()) {
    return;
  }

  vec[current_level].push_back(
      std::shared_ptr<ColoredNode<T>>(new ColoredNode(elem)));

  RecursiveDumpFullBinaryTree(vec, elem == nullptr ? nullptr : elem->left_,
                              current_level + 1);
  RecursiveDumpFullBinaryTree(vec, elem == nullptr ? nullptr : elem->right_,
                              current_level + 1);
}

template <typename T>
size_t Treap<T>::RecursiveCount(std::shared_ptr<Node<T>> tree,
                                const T& data) const {
  if (tree == nullptr) {
    return 0;
  }

  return (tree->data_ == data) + (tree->data_ > data
                                      ? RecursiveCount(tree->left_, data)
                                      : RecursiveCount(tree->right_, data));
}

template <typename T>
void Treap<T>::PrintDataAndPriority(Color color,
                                    std::shared_ptr<Node<T>> elem) const {
  std::cout << "\n  Данные: " << color;

  if (elem) {
    std::cout << elem->data_;
  } else {
    std::cout << '#';
  }

  std::cout << Color::kDefault;
  std::cout << "\n  Приоритет:  " << color;

  if (elem) {
    std::cout << elem->priority_;
  } else {
    std::cout << '#';
  }
  std::cout << Color::kDefault;
}

template <typename T>
void Treap<T>::PaintPartOfTree(
    std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> tree,
    std::shared_ptr<Node<T>> elem, Color color_vertex,
    Color color_other) const {
  if (!elem) {
    return;
  }

  bool is_find = false;
  size_t first_colored = 0, last_colored = 0;
  size_t len_colored = 1;
  for (size_t i = 0; i < tree.size(); ++i) {
    for (size_t j = 0; j < tree[i].size(); ++j) {
      if (tree[i][j] && elem == tree[i][j]->node) {
        is_find = true;
        first_colored = j;
        tree[i][j]->color = color_vertex;
      } else if (is_find && first_colored <= j && j < last_colored) {
        tree[i][j]->color = color_other;
      }
    }
    if (is_find) {
      first_colored <<= 1;
      len_colored <<= 1;
      last_colored = first_colored + len_colored;
    }
  }
}

template <typename T>
size_t Treap<T>::MaxLenghtOfElement() const {
  std::queue<std::shared_ptr<Node<T>>> queue;
  size_t element_length = 0;

  if (head_ != nullptr) {
    queue.push(head_);
  }

  while (!queue.empty()) {
    std::shared_ptr<Node<T>> elem = queue.front();
    queue.pop();

    if (elem != nullptr) {
      std ::stringstream ss;
      ss << elem->data_;
      element_length = std::max(element_length, ss.str().size());

      queue.push(elem->left_);
      queue.push(elem->right_);
    }
  }
  return element_length;
}

template <typename T>
std::ostream& Treap<T>::PrintFullBinaryTree(
    std::ostream& out,
    std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> tree) const {
  const size_t height = GetHeight();
  size_t element_length = MaxLenghtOfElement();
  for (int current_level = 0; current_level < height; ++current_level) {
    if (current_level) {
      out << '\n';
    }
    for (int i = 0; i < tree[current_level].size(); ++i) {
      size_t cell_width = height - current_level + 1;
      if (!i) {
        --cell_width;
      }
      out << tree[current_level][i]->color;
      out << std::setw((1 << cell_width) * element_length);
      if (tree[current_level][i]->node) {
        out << tree[current_level][i]->node->data_;
      } else {
        out << '#';
      }
    }
    out << Color::kDefault;
  }

  if (!height) {
    out << " #";
  }

  return out;
}

template <typename T>
void Treap<T>::PrintSeparator(Color color, int length, char separator) const {
  std::cout << color << std::setfill(separator) << std::setw(length) << ' '
            << std::setfill(' ') << '\n'
            << Color::kDefault;
}

template <typename T>
void Treap<T>::PrintAndPaintFullBinaryTree(std::shared_ptr<Node<T>> tree,
                                           Color color_vertex,
                                           Color color_other) const {
  auto vec = DumpFullBinaryTree();
  PaintPartOfTree(vec, tree, color_vertex, color_other);
  PrintFullBinaryTree(std::cout, vec);
  std::cout << '\n';
}

template <typename T>
void Treap<T>::PrintRemoveInfo(const T& data) const {
  std::cout << "Удаляемый элемент:";
  std::cout << "\n  Данные: " << Color::kGreen << data << Color::kDefault
            << '\n';
  std::cout << "  Приоритет: " << Color::kGreen << "#" << Color::kDefault;
  std::cout << "\nРассматриваемый элемент (" << Color::kRed << "T"
            << Color::kDefault << ") дерева:";
}

template <typename T>
void Treap<T>::PrintRemoveIfEqual(std::shared_ptr<Node<T>> tree) const {
  std::cout << "Данные совпадают\n\n";
  std::cout << Color::kWave
            << "Слияние двух дерамид, двух потомков рассматриваемого "
               "элемента дерева в одну дерамиду:\n"
            << Color::kDefault;
  std::cout << Color::kWave << "Левый потомок (" << Color::kRed << "T1"
            << Color::kWave << "):\n"
            << Color::kDefault;
  Treap temp(tree->left_);
  std::cout << temp << '\n';

  std::cout << Color::kWave << "Правый потомок (" << Color::kRed << "T2"
            << Color::kWave << "):\n"
            << Color::kDefault;
  temp = tree->right_;
  std::cout << temp << '\n';
}

template <typename T>
void Treap<T>::PrintMerge(std::shared_ptr<Node<T>> tree) const {
  std::cout << Color::kWave << "Слияние:\n" << Color::kDefault;
  Treap temp(tree);
  std::cout << temp << '\n';

  std::cout << Color::kWave
            << "Добавление слитой дерамиды вместо удаляемоего элемента:\n"
            << Color::kDefault;
  PrintAndPaintFullBinaryTree(tree, Color::kRed, Color::kGreen);
}