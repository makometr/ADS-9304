#include "List.h"


Node* createList(std::vector<Node*> &nodes, std::vector<int> N){
	Node* list = min(nodes, N);
	Node* cur = list;
	int size = nodes.size();
	for(int i = 0;i < size;i++){
		cur->next = min(nodes, N);
		if(cur->next == nullptr)
			break;
		cur = cur->next;
	}
	cur = list;
	while(cur != nullptr){
		if(cur->isKnot == true){
            cur->value = createList(nodes,cur->number);
    	}
		cur = cur->next;
	}
	return list;
}

Node* min(std::vector<Node*> &nodes, std::vector<int> N){
	Node* min=nullptr;
	int m=-1;
	int count = 0;
	for(int i = 0;i < nodes.size();i++){
		if(nodes[i]->number.size() == N.size()+1){
			for(int j = 0;j < N.size();j++){
                if(nodes[i]->number[j] == N[j]){
                    count++;
                }
            }
			if(count == N.size()){
				min = nodes[i];
				m = i;
				count =0;
				break;
			}
		}
		count =0;
	}
	if(min == nullptr){
		return min;
	}
	for(int i = 0;i < nodes.size();i++){
		if(nodes[i]->number.size() == N.size()+1){
			for(int j = 0;j < N.size();j++){
				if(nodes[i]->number[j] == N[j]){
					count++;
				}
			}
			if(count == N.size() && nodes[i]->number[nodes[i]->number.size()-1] < min->number[min->number.size()-1]){
            	min = nodes[i];
            	m = i;
        	}
        	count = 0;
		}
    }
	if(m != -1){
		for(int i = m;i < nodes.size()-1;i++){
			nodes[i] = nodes[i+1];
		}
		nodes.pop_back();
	}
	return min;
}

void printList(Node* node, int N){
	Node* cur = node;
	Node* oldCur;
	while(cur){
		for(int i=0;i<N;i++)
			std::cout << '\t';
		cur->print();
		if(std::get_if<Node*>(&cur->value)){
			oldCur = cur;
			cur = std::get<Node*>(cur->value);
			printList(cur, N+1);
			cur = oldCur;
		}
		cur = cur->next;
	}
}


List::List(std::string file){
	std::vector<Node*> nodes;
	std::ifstream f(file);
	std::string str;
	if(f.is_open()){
    	while(getline(f,str)){
			nodes.push_back(new Node(str));
		}
	}
	if(nodes[nodes.size() -1]->number.size()==0){
		nodes.pop_back();
	}
	this->firstElem = createList(nodes);
	for(int i = 0;i<nodes.size();i++)
		delete nodes[i];

}

void List::addElem(std::string newElem){
	Node* node = new Node(newElem);
	Node* cur = this->firstElem;
	Node* next;
	for(int i = 0;i < node->number.size()-1;i++){
		while(node->number[i] != cur->number[i]){
			cur = cur->next;
		}
		try{
			if(cur->isKnot!=true)
				throw 1;
			else
				cur = std::get<Node*>(cur->value);
		}catch(int){
			std::cout << "ERROR: an element isn't a knot\n";
			exit(0);
		}
	}
	while(node->number[node->number.size()-1] >= cur->next->number[cur->next->number.size()-1]){
		try{
			cur = cur->next;
			if(cur->next == nullptr)
				break;
			if(node->number[node->number.size()-1] == cur->number[cur->number.size()-1])
				throw 1;
		}catch(int){
			std::cerr << "ERROR: an element with this number exists\n";
			exit(0);
		}
	}
	if(cur->next != nullptr){
        next = cur->next;
        cur->next = node;
        node->next = next;
    }
    if(cur->next == nullptr){
		cur->next = node;
        node->next = nullptr;
	}
}

void List::deleteElem(std::vector<int> elem){
	Node* cur = this->firstElem;
	Node* knot;
	for(int i = 0;i < elem.size()-1;i++){
        while(elem[i] != cur->number[i]){
            cur = cur->next;
        }
        
		try{
            if(cur->isKnot!=true)
                throw 1;
            else
                knot = cur;
				cur = std::get<Node*>(cur->value);
        }catch(int){
            std::cout << "ERROR: an element isn't a knot\n";
            exit(0);
        }
	}
		
		if(elem[elem.size()-1] == cur->number[cur->number.size()-1]){
			if(cur == this->firstElem)
				this->firstElem = cur->next;
			knot->value = cur->next;
			if(cur->isKnot == true){
                clean(std::get<Node*>(cur->next->value));
            }
			delete cur;
		}else{
			try{
			while(elem[elem.size()-1] != cur->next->number[cur->next->number.size()-1]){
				cur = cur->next;
				if(cur->next == nullptr){
					throw 1;
					break;
				}
			}
			
			}catch(int a){
        		std::cerr << "ERROR: an element doesn't exist\n";
        		exit(0);
    		}

			Node* prev = cur;
			Node* next = cur->next->next;
			if(cur->next->isKnot == true){
				clean(std::get<Node*>(cur->next->value));
			}
			delete cur->next;
			prev->next = next;
	}
}

void List::deleteElem(std::string elem, Node* cur){
	if(cur == nullptr)
		cur = this->firstElem;
	Node* next;
	while(cur->next != nullptr){
		if(std::get_if<Node*>(&cur->value)){
			if(std::get<Node*>(cur->value)->name == elem){
				next = std::get<Node*>(cur->value);
				cur->value = std::get<Node*>(cur->value)->next;
				delete next;
				break;
			}
		}
		if(cur->next->name == elem){
			next = cur->next;
			cur->next = cur->next->next;
			delete next;
			break;
		}
		if(cur->isKnot == true && std::get<Node*>(cur->value) != nullptr){
			deleteElem(elem, std::get<Node*>(cur->value));
		}
		cur = cur->next;
	}
}

void List::changeName(std::vector<int> elem, std::string newName){
	Node* cur = this->firstElem;
    for(int i = 0;i < elem.size()-1;i++){
        while(elem[i] != cur->number[i]){
            cur = cur->next;
        }
        try{
            if(cur->isKnot!=true)
                throw 1;
            else
                cur = std::get<Node*>(cur->value);
        }catch(int){
            std::cout << "ERROR: an element isn't a knot\n";
            exit(0);
        }
    }
	if(elem[elem.size()-1] == cur->number[cur->number.size()-1]){
		cur->name = newName;
    }else{
    	try{
		while(elem[elem.size()-1] != cur->number[cur->next->number.size()-1]){
	        cur = cur->next;
			if(cur->next == nullptr){
                    throw 1;
                    break;
            }
		}

        }catch(int a){
            std::cerr << "ERROR: an element doesn't exist\n";
        	exit(0);
    	}
		cur->name = newName;
	}
}

void List::changeNumber(std::vector<int> number, std::vector<int> newNumber){
	Node* cur = this->firstElem;
	Node* newNode;
	Node* knot;
	Node* next;
	for(int i = 0;i < number.size()-1;i++){
        while(number[i] != cur->number[i]){
			cur = cur->next;
        }
        try{
            if(cur->isKnot!=true)
                throw 1;
            else
                knot = cur;
                cur = std::get<Node*>(cur->value);
        }catch(int){
            std::cout << "ERROR: an element isn't a knot\n";
            exit(0);
        }
    }

    if(number[number.size()-1] == cur->number[cur->number.size()-1]){
        cur->number = newNumber;
		newNode = cur;
		knot->value = cur->next;
    }else{
    	try{
        while(number[number.size()-1] != cur->next->number[cur->next->number.size()-1]){
			cur = cur->next;
            if(cur->next == nullptr){
                    throw 1;
                    break;
            }
		}

        }catch(int a){
            std::cerr << "ERROR: an element doesn't exist\n";
            exit(0);
        }

	
		cur->next->number = newNumber;
    	newNode = cur->next;
    	next = cur->next->next;
    	cur->next = next;
	}
	cur = this->firstElem;
    next = nullptr;
    for(int i = 0;i < newNode->number.size()-1;i++){
        while(newNode->number[i] != cur->number[i]){
			cur = cur->next;
        }

        try{
            if(cur->isKnot!=true)
                throw 1;
            else
                cur = std::get<Node*>(cur->value);
        }catch(int){
            std::cout << "ERROR: an element isn't a knot\n";
            exit(0);
        }
    }
	
	while(newNode->number[newNode->number.size()-1] >= cur->number[cur->number.size()-1]){
        
		try{

            if(cur->next == nullptr)
                break;
			else
            	cur = cur->next;
            if(newNode->number[newNode->number.size()-1] == cur->number[cur->number.size()-1])
                throw 1;
        }catch(int){
            std::cerr << "ERROR: an element with this number exists\n";
            exit(0);
        }
    }

    if(cur->next != nullptr){
        next = cur->next;
        cur->next = newNode;
        newNode->next = next;
    }
    if(cur->next == nullptr){
        cur->next = newNode;
        newNode->next = nullptr;
    }
	cur = cur->next;
}

void clean(Node* node){
	if(node != nullptr){
		Node* cur = node;
		Node* prev;
		while(cur->next != nullptr){
			if(cur->isKnot == true){
				clean(std::get<Node*>(cur->value));
			}
			prev = cur;
			cur = cur->next;
			delete prev;
		}
		delete cur;
	}
}

void List::print(){
	int N=0;
	printList(this->firstElem, N);
}

List::~List(){
	clean(this->firstElem);	
};


