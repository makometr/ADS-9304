#pragma once

template<typename base>
class Node{
    base data;
public:
    Node(base newData);
    base getData();
};



template<typename base>
Node<base>::Node(base newData){
    data = newData;
}

template<typename base>
base Node<base>::getData(){
    return data;
}
