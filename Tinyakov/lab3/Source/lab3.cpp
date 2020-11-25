#include <iostream>
#include <memory>
#include <utility>
#include <cwchar>
#include <cwctype>
#include <clocale>
#include <vector>
#include <cmath>
#include <algorithm>

#define ALP_POWER 32


template<typename T>
class BinTreeNode{
public:
    T data;
    std::shared_ptr<BinTreeNode<T>> left{nullptr}, right{nullptr};
    std::weak_ptr<BinTreeNode<T>> parent;
    BinTreeNode() = default;

    BinTreeNode(T& data){
        this->data = data;
    }
    
    BinTreeNode(T&& data){
        this->data = data;
    }

    ~BinTreeNode() = default;
    
    BinTreeNode(const BinTreeNode<T>& node){
        data = node.data;
        left = node.left;
        right = node.right;
        parent = node.parent;
    }

    BinTreeNode& operator=(const BinTreeNode<T>& node){
        if(&node == this) return *this;
        data = node.data;
        left = node.left;
        right = node.right;
        parent = node.parent;
        return *this;
    }
    
    BinTreeNode(const BinTreeNode<T>&& node){
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
    }

    BinTreeNode& operator=(const BinTreeNode<T>&& node){
        if(&node == this) return *this;
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }
};

template<typename T>
class BinTree{
using NodePtr = std::shared_ptr<BinTreeNode<T>>;
//using ParentPtr = std::weak_ptr<BinTreeNode<T>>
protected:
    NodePtr head{nullptr};
public:
    BinTree() = default;
    ~BinTree() = default;

    BinTree(const BinTree<T>& tree){
        auto Copy = [](NodePtr parent, NodePtr& dest, const NodePtr& src,  auto&& Copy)->void{
            if(src == nullptr) return;
            dest = std::make_shared<BinTreeNode<T>>(src->data);
            dest->parent = parent;
            Copy(dest, dest->left, src->left, Copy);
            Copy(dest, dest->right, src->right, Copy);
        };
        Copy(nullptr, head, tree.head, Copy);
    }
    
    BinTree& operator=(const BinTree<T>& tree){
        if(&tree == this) return *this;
        auto Copy = [](NodePtr parent, NodePtr& dest, const NodePtr& src,  auto&& Copy)->void{
            if(src == nullptr) return;
            dest = std::make_shared<BinTreeNode<T>>(src->data);
            dest->parent = parent;
            Copy(dest, dest->left, src->left, Copy);
            Copy(dest, dest->right, src->right, Copy);
        };
        Copy(nullptr, head, tree.head, Copy);
        return *this;
    }

    BinTree(BinTree<T>&& tree){
        head = std::move(tree.head);
    }
    
    BinTree& operator=(BinTree<T>&& tree){
        if(&tree == this) return *this;
        head = std::move(tree.head);
        return *this;
    }

    void Insert(T new_data){
        if(head == nullptr){
            head = std::make_shared<BinTreeNode<T>>(new_data);
            return;
        }
        NodePtr cur = head;
        while(true){
            if(new_data == cur->data){
                cur->data = new_data;
                break;
            }
            if(new_data < cur->data){
                if(cur->left == nullptr){
                    cur->left = std::make_shared<BinTreeNode<T>>(new_data);
                    cur->left->parent = cur;
                    break;
                }else{
                    cur = cur->left;
                }
            }
            if(new_data > cur->data){
                if(cur->right == nullptr){
                    cur->right = std::make_shared<BinTreeNode<T>>(new_data);
                    cur->right->parent = cur;
                    break;
                }else{
                    cur = cur->right;
                }
            }
        }
    }

    void Print(){
        auto print = [](NodePtr node, auto&& print)->void{
            if(node == nullptr) return;
            print(node->left, print);
            std::cout<<node->data<<" ";
            print(node->right, print);
        };
        print(head, print);
        std::cout<<"\n";
    }

    void Delete(T del){
        if(head == nullptr) return;
        if(head->data == del){
            head = nullptr;
            return;
        }
        auto cur = head;
        while(true){
            if(del < cur->data){
                if(cur->left == nullptr) break;
                if(cur->left->data == del){
                    cur->left = nullptr;
                    break;
                }
                cur = cur->left;
            }else{
                if(cur->right == nullptr) break;
                if(cur->right->data == del){
                    cur->right = nullptr;
                    break;
                }
                cur = cur->right;
            }
        }
    }

    T Find(T find){
        if(head == nullptr) throw std::logic_error("Tree is empty");
        auto cur = head;
        while(true){
            if(find == cur->data) return cur->data;
            if(find < cur->data){
                if(cur->left == nullptr) throw std::logic_error("Not find");
                cur = cur->left;
            }else{
                if(cur->right == nullptr) throw std::logic_error("Not find");
                cur = cur->right;
            }
        }
    }
        
};

/*template<typename T, typename U>
std::pair<T,U> operator-(std::pair<T,U> a, std::pair<T,U> b){
    return std::pair((a.first-b.first), (a.second-b.second));
}*/

class BinTreeAlp: public BinTree<std::pair<float, wchar_t>>{
using Pair = std::pair<float, wchar_t>;
public:
    BinTreeAlp() = default;
    ~BinTreeAlp() = default;
    
    BinTreeAlp(BinTreeAlp&& tree){
        head = std::move(tree.head);
    }
    
    BinTreeAlp& operator=(BinTreeAlp tree){
        if(&tree == this) return *this;
        head = std::move(tree.head);
        return *this;
    }

     Pair Find(float find){
        if(head == nullptr) throw std::logic_error("Tree is empty");
        Pair ret = head->data;
        float delta = fabs(find - head->data.first);
        auto cur = head;
        while(true){
            if(find < cur->data.first){
                if(cur->left == nullptr) break;
                cur = cur->left;
            }else{
                if(cur->right == nullptr) break;
                cur = cur->right;
            }
            if(delta > fabs(find - cur->data.first)){
                delta = fabs(find - cur->data.first);
                ret = cur->data;
            }
        }
        return ret;
     }
};

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> pair){
    os << pair.first << " " << pair.second;
    return os;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout<<"Missing argument. Usage: lab3 <encode/decode/hack>\n";
        return 1;
    }
    setlocale(LC_ALL,"ru_RU.utf8");
    std::string cmd(argv[1]);
    std::wcin.unsetf(std::ios_base::skipws);
    if(cmd == "encode" || cmd == "decode"){
        int shift;
        std::wcin >> shift;
        while(shift < 0) shift += ALP_POWER;
        shift = (cmd == "encode")? (shift % ALP_POWER) : (ALP_POWER - (shift % ALP_POWER));
        wchar_t c;
        std::wcin >> c;
        std::wcin >> c;
        while(c != L'D' && !std::wcin.eof()){
            if(!((c >= L'А'&& c <= L'я') || c < L'A' || c == L'ё' || c == L'Ё')){
                std::wcout << L"Error, character is not russian: \'"<< c << "\'\n";
                return 1;
            }
            if(c == L'Ё') c = L'Е';
            if(c == L'ё') c = L'е';
            if(iswalpha(c)){
                if(iswlower(c))std::wcout << (wchar_t)towlower((((c - L'а') + shift) % ALP_POWER) + L'а');
                else std::wcout << (wchar_t)towupper((((towlower(c) - L'а') + shift) % ALP_POWER) + L'а');
            }else std::wcout << c;
            std::wcin >> c;
        }
    } else if(cmd == "hack"){
        std::vector<std::pair<long, wchar_t>> chars;
        chars.assign(ALP_POWER, std::pair(0,0));
        for(int i = 0; i < chars.size(); i++)
            chars[i] = std::pair(0, L'а' + i);
        long size = 0;
        wchar_t c;
        std::wcin >> c;
        std::wstring text;
        while(c != L'D' && !std::wcin.eof()){
            if(!((c >= L'А'&& c <= L'я') || c < L'A' || c == L'ё' || c == L'Ё')){
                std::wcout << L"Error, character is not russian: \'"<< c << "\'\n";
                return 1;
            }
            if(c == L'Ё') c = L'Е';
            if(c == L'ё') c = L'е';
            if(iswalpha(c)){
                size++;
                chars[((towlower(c) - L'а') % ALP_POWER)].first++;
            }
            text += c;
            std::wcin >> c;
        }
        auto GenTree = []()->BinTreeAlp{
            BinTreeAlp tree;
            tree.Insert(std::pair<float, wchar_t>(0.0262, L'у'));
            tree.Insert(std::pair<float, wchar_t>(0.0144, L'ч'));
            tree.Insert(std::pair<float, wchar_t>(0.0048, L'ц'));
            tree.Insert(std::pair<float, wchar_t>(0.0026, L'ф'));
            tree.Insert(std::pair<float, wchar_t>(0.0004, L'ъ'));
            tree.Insert(std::pair<float, wchar_t>(0.0032, L'э'));
            tree.Insert(std::pair<float, wchar_t>(0.0036, L'щ'));
            tree.Insert(std::pair<float, wchar_t>(0.0094, L'ж'));
            tree.Insert(std::pair<float, wchar_t>(0.0064, L'ю'));
            tree.Insert(std::pair<float, wchar_t>(0.0073, L'ш'));
            tree.Insert(std::pair<float, wchar_t>(0.0097, L'х'));
            tree.Insert(std::pair<float, wchar_t>(0.0121, L'й'));
            tree.Insert(std::pair<float, wchar_t>(0.0174, L'ь'));
            tree.Insert(std::pair<float, wchar_t>(0.0165, L'з'));
            tree.Insert(std::pair<float, wchar_t>(0.0159, L'б'));
            tree.Insert(std::pair<float, wchar_t>(0.0170, L'г'));
            tree.Insert(std::pair<float, wchar_t>(0.0190, L'ы'));
            tree.Insert(std::pair<float, wchar_t>(0.0201, L'я'));
            tree.Insert(std::pair<float, wchar_t>(0.0547, L'с'));
            tree.Insert(std::pair<float, wchar_t>(0.0349, L'к'));
            tree.Insert(std::pair<float, wchar_t>(0.0298, L'д'));
            tree.Insert(std::pair<float, wchar_t>(0.0281, L'п'));
            tree.Insert(std::pair<float, wchar_t>(0.0321, L'м'));
            tree.Insert(std::pair<float, wchar_t>(0.0454, L'в'));
            tree.Insert(std::pair<float, wchar_t>(0.0440, L'л'));
            tree.Insert(std::pair<float, wchar_t>(0.0473, L'р'));
            tree.Insert(std::pair<float, wchar_t>(0.0735, L'и'));
            tree.Insert(std::pair<float, wchar_t>(0.0626, L'т'));
            tree.Insert(std::pair<float, wchar_t>(0.0670, L'н'));
            tree.Insert(std::pair<float, wchar_t>(0.0849, L'е'));
            tree.Insert(std::pair<float, wchar_t>(0.0801, L'а'));
            tree.Insert(std::pair<float, wchar_t>(0.1097, L'о'));
            return tree;
        };
        BinTreeAlp tree = GenTree();
        std::sort(chars.begin(), chars.end(), [](std::pair<long,wchar_t> a, std::pair<long,wchar_t> b)->bool{ return a>b;});
        std::vector<wchar_t> geted_chars;
        auto find_char = [&geted_chars](wchar_t c)->bool{
            for(int i = 0; i<geted_chars.size(); i++)
                if(geted_chars[i] == c) return true;
            return false;
        };
        std::vector<int> shifts;
        shifts.assign(ALP_POWER, 0);
        int neg = 0;
        for(int i = 0; i < chars.size(); i++){
            float freq = (float)chars[i].first/size;
            std::pair<float, wchar_t> pair = tree.Find(freq);
            while(freq > 0.0 && find_char(pair.second)){
                freq -= 0.001;
                pair = tree.Find(freq);
            }
            geted_chars.push_back(pair.second);
            int char_shift = (pair.second - chars[i].second);
            if(char_shift < 0){
                char_shift += ALP_POWER;
                neg++;
            }
            shifts[char_shift % ALP_POWER]++;
        }
        int shift = 1, shift_power = shifts[0];
        for(int i = 1; i < shifts.size(); i++)
            if(shifts[i] > shift_power){
                shift = i;
                shift_power = shifts[i];
            }
        for(int i = 0; i < text.size(); i++){
            if(!iswalpha(text[i])) continue;
            if(iswlower(text[i])) text[i] = (wchar_t)towlower((((text[i] - L'а') + shift) % ALP_POWER) + L'а');
            else text[i] = (wchar_t)towupper((((towlower(text[i]) - L'а') + shift) % ALP_POWER) + L'а');
        }
        std::wcout << text <<L"\n";
    } else {
        std::cout<<"Wrong argument. Usage: lab3 <encode/decode/hack>\n";
        return 1;
    }
    return 0;
}
