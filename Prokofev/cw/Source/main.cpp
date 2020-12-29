#include <iostream>
#include <memory>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iftream>
#include <time.h>

static int c_ins = 0;
static int del_ins = 0;

class binSTree{
public:
    int info;
    int count;
    int number;
    std::shared_ptr<binSTree> hd {nullptr};
    std::shared_ptr<binSTree> lt {nullptr};
    std::shared_ptr<binSTree> rt {nullptr};
};

int chance(int random)
{
    return (rand()%random);
}

void to_rotate_right(std::shared_ptr<binSTree>& t)
{
    c_ins++;
    std::shared_ptr<binSTree> x;
    if(t==nullptr)
        std::cout<<"to_rotate_right(NULL)"<<std::endl;
    else
    {
        x=t->lt;
        t->lt=x->rt;
        x->rt=t;
        t=x;
    }
}

void to_rotate_left(std::shared_ptr<binSTree>& t)
{
    c_ins++;
    std::shared_ptr<binSTree> x;
    if(t==nullptr)
        std::cout<<"to_rotate_right(NULL)"<<std::endl;
    else
    {
        x=t->rt;
        t->rt = x->lt;
        x->lt=t;
        t=x;
    }
}

void Insert_to_begin(std::shared_ptr<binSTree>& b, int x)
{
    c_ins++;
    if(b==nullptr){
        b = std::make_shared<binSTree>();
        if(b!=nullptr){
            b->info=x;
            b->count=1;
        }else{
            std::cout << "1 Memory not enough\n";
            exit(1);
        }

    }else if(x<b->info) {
            Insert_to_begin(b->lt, x);
        to_rotate_right(b);
    }else if(x>b->info){
            Insert_to_begin(b->rt, x);
        to_rotate_left(b);
    }
    else b->count++;
}

void r_Insert(std::shared_ptr<binSTree>& b, int x){
    c_ins++;
    if(b==nullptr)
    {
        b = std::make_shared<binSTree>();
        if(b!=nullptr)
        {
            b->info=x;
            b->count=1;
            b->number=1;
            return;
        }
        else
        {
            std::cout << "1 Memory not enough\n";
            exit(1);
        }
    }
    if(rand()%(b->number+1) == 0)
    {
        Insert_to_begin(b,x);
        return;
    }
    if(x<b->info)
            r_Insert(b->lt, x);
    else {
            r_Insert(b->rt, x);
    }
}

void fix_numb(std::shared_ptr<binSTree>& b){
    if(b){
        if(b->lt && b->rt){
            b->number = 2;
            fix_numb(b->lt);
            fix_numb(b->rt);
            b->number +=  b->lt->number;
            b->number +=  b->rt->number;
        }
        if(b->lt && !b->rt){
            b->number = 1;
            fix_numb(b->lt);
            b->number +=  b->lt->number;
        }
        if(!b->lt && b->rt){
            b->number = 1;
            fix_numb(b->rt);
            b->number +=  b->rt->number;
        }
    }
}

int f_min(std::shared_ptr<binSTree>& p, int& ct){
    std::shared_ptr<binSTree> temp = std::make_shared<binSTree>();
    temp = p;
    while(temp->lt)
        temp = temp->lt;
    ct = temp->count;
    return temp->info;
}

int f_max(std::shared_ptr<binSTree>& p, int& ct){
    std::shared_ptr<binSTree> temp = std::make_shared<binSTree>();
    temp = p;
    while(temp->rt)
        temp = temp->rt;
    ct = temp->count;
    return temp->info;
}


void r_Delete(std::shared_ptr<binSTree>& ptr,int info){
    del_ins++;
    if(ptr){
        if(ptr == ptr->hd && !ptr->lt && !ptr->rt){
            ptr->hd = nullptr;
            return;
        }
        if(info < ptr->info){
            r_Delete(ptr->lt,info);
        }else if (info > ptr->info){
            r_Delete(ptr->rt,info);
        }else if (info == ptr->info){
            if(!ptr->lt && !ptr->rt){
                ptr = nullptr;
            }else if (ptr->rt){
                int lt_time = f_min(ptr->rt, ptr->count);
                r_Delete(ptr->rt, lt_time);
                ptr->info = lt_time;
            }else if (ptr->lt){
                int rt_time = f_max(ptr->lt ,ptr->count);
                r_Delete(ptr->lt, rt_time);
                ptr->info = rt_time;
            }
        }
    }else{
        std::cout << "There is no input_intent " << info << " in tree.\n";
    }
}

void drawTree(std::shared_ptr<binSTree> curNode, int level, int direction)
{
    if(curNode)
    {
        drawTree(curNode->rt,level + 1, 1);
        for(int i = 0;i< level;i++) std::cout<<"    ";
        if(direction == 1) std::cout << "/ ";
        else if(direction == 2) std::cout << "\\ ";
        std::cout << curNode->info << std::endl;
        drawTree(curNode->lt,level + 1, 2);
    }
}

void print(std::shared_ptr<binSTree> curNode){
    if(curNode == nullptr)
        return;
    print(curNode->lt);
    std::cout << curNode->info;
    print(curNode->rt);
}


class rd{
    std::ofstream r_file;
public:

    void rs_Insert(int size = 16384, bool r_case){
        r_file.open("insert_test.txt");
        std::vector<int> insert_v;
        std::shared_ptr<binSTree> My_Tree = nullptr;
        if(r_case)
            create_unsorted(size, insert_v);
        else
            create_sorted(size, insert_v);
        for(int i = 0; i < size; i++) {
            c_ins = 0;
            r_Insert(My_Tree, insert_v[i]);
            fix_numb(My_Tree);
            r_file << i << " " << c_ins << "\n";
        }
        r_file.close();
    }


    void rs_Delete(int size = 8192, bool r_case){
        srand(time(0));
        r_file.open("delete_test.txt");
        std::vector<int> insert_v;
        std::shared_ptr<binSTree> My_Tree = nullptr;
        if(r_case)
            create_unsorted(size, insert_v);
        else
            create_sorted(size, insert_v);
        for(int j = 0; j < size; j++){
            r_Insert(My_Tree, insert_v[j]);
            fix_numb(My_Tree);
        }
        for(int i = 0; i < size; i++) {
            del_ins = 0;
            r_Delete(My_Tree, insert_v[insert_v.size() - 1 - i]);
            r_file << size - 1 - i << " " << del_ins << "\n";
        }
        r_file.close();
    }


    void create_unsorted(int count, std::vector<int>& insert_v) {
        int temp;
        for(int i = 0; i < count; i++)
            insert_v.push_back(i);
        for(int i = count - 1; i >= 1; i--) {
            int j = rand()%(count);
            temp = insert_v[j];
            insert_v[j] = insert_v[i];
            insert_v[i] = temp;
        }
    }

    void create_sorted(int count, std::vector<int>& insert_v){
        for (int i = count; i > 0; i--)
            insert_v.push_back(i);
    }
};

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    std::ifstream in("input.txt");
    std::string s;
    getline(in, s);
    std::cout << "Input:" << "\n" << s << "\n";
    std::shared_ptr<binSTree> My_Tree = nullptr;
    std::istringstream n(s);
    int input_int;
    while (n >> input_int) {
        r_Insert(My_Tree, input_int);
    }
    std::string choice;
    std::string int_str;
    while(true)
    {
        std::cout <<"\nPicture:\n";
        drawTree(My_Tree, 0, 0);
        std::cout << "\nChoose action:\n'+' - for insert element\n'-' - for delete element\nOr print \"esc\" for exit\n";
        getline(in, choice);
        if(choice == "+")
            {
                std::cout << "Input the input_intent for insert:\n";
		getline(in, int_str);
		int input_int2 = atoi(int_str.c_str());
                std::cin >> input_int2;
                r_Insert(My_Tree, input_int2);
            }
        if(choice == "-")
            {
                std::cout << "Input the input_intent for delete:\n";
		getline(in, int_str);
		int input_int2 = atoi(int_str.c_str());
                std::cin >> input_int2;
                r_Delete(My_Tree, input_int2);
            }
        if(choice == "esc")
            {
                break;
            }
        
    }
    std::cout << "Finish";
    return 0;
}
