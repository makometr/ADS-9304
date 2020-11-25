#pragma once

template<typename base>
class Node{
    base data;
public:
    Node(base newData);
    base getData();
    void setData(base newData);
};



template<typename base>
Node<base>::Node(base newData){
    data = newData;
}

template<typename base>
base Node<base>::getData(){
    return data;
}



template<typename base>
void Node<base>::setData(base newData){
    data = newData;
}