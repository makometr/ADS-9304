#include <iostream>
#include <memory>
#include "string.h"

class binSTree{
public:
    char info;
    int count;
    int number;
    std::shared_ptr<binSTree> lt {nullptr};
    std::shared_ptr<binSTree> rt {nullptr};
};


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
    if(curNode == nullptr){
        return;
    }
    print(curNode->lt);
    std::cout << curNode->info;
    print(curNode->rt);
}


bool chance(int random)
{
    srand(time(0));
    return !(rand() % random);
}

void to_rotate_right(std::shared_ptr<binSTree>& t)
{
std::shared_ptr<binSTree> x;
if(t==NULL)
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
std::shared_ptr<binSTree> x;
if(t==NULL)
	std::cout<<"to_rotate_right(NULL)"<<std::endl;
else
	{
	x=t->rt;
	t->rt = x->lt;
	x->lt=t;
	t=x;
	}
}

void Insert_to_begin(std::shared_ptr<binSTree>& b, char x)
{
if(b==NULL)
	{
	b = std::make_shared<binSTree>();
	if(b!=NULL)
		{
		b->info=x;
		b->count=1;
		}
	else
		{
		std::cout << "1 Memory not enough\n";
		exit(1);
		}

	}
else
if(x<b->info)
	{
	Insert_to_begin(b->lt, x);
	to_rotate_right(b);
	}
else if(x>b->info)
	{
	Insert_to_begin(b->rt, x);
	to_rotate_left(b);
	}
else b->count++;
}



void r_Insert(std::shared_ptr<binSTree>& b, char x)
{
if(b==NULL)
	{
	b = std::make_shared<binSTree>();
	if(b!=NULL)
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
if(chance(b->number+1))
		{
		Insert_to_begin(b,x);
		return;
		}
if(x<b->info)
	r_Insert(b->lt, x);
else
	r_Insert(b->rt, x);
b->number++;
}



int main(int argc, char* argv[])
{
    char* text;
    strcpy(text, argv[1]);
    std::shared_ptr<binSTree> My_Tree = NULL;
    for(int i=0; text[i]; i++)
        r_Insert(My_Tree, text[i]);
    print(My_Tree);
    std::cout <<"\n";
    drawTree(My_Tree, 0, 0);
    return 0;
}