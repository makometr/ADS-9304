#include<iostream>
#include<memory>
#include<variant>
#include<cctype>

//#define DEBUG

template<typename base>
class Node{
using NodePtr = std::shared_ptr<Node>;
public:
    NodePtr next {nullptr};
    std::variant<NodePtr, base> value;
};

int main(){
    std::istream& input = std::cin;
    std::ostream& output = std::cout;

    // cos == &
    // sin == $
    auto GetExpr = [&input](auto&& GetExpr)->std::shared_ptr<Node<char>>{
        char c;
        input >> c;
        if(c != '(') throw std::logic_error("Invalid input\n");
        auto head = std::make_shared<Node<char>>();
        input >> c;
        if(input.eof()) throw std::logic_error("Invalid input\n");
        switch(c){
            case '+':
            case '-':
            case '*':
            case '/':
                {
                    head->value = c;
                    head->next = std::make_shared<Node<char>>();
                    head->next->value = GetExpr(GetExpr);
                    if((c == '-' || c == '+') && input.peek() != EOF && input.peek() == ')'){
                        input >> c;
                        return head;
                    }
                    head->next->next = std::make_shared<Node<char>>();
                    head->next->next->value = GetExpr(GetExpr);
                    input >> c;
                    if(input.eof()) throw std::logic_error("Invalid input\n");
                    if(c == ')') return head;
                    throw std::logic_error("Invalid input\n");
                }
            case 'c':
                input >> c;
                if(input.eof()) throw std::logic_error("Invalid input\n");
                if(c == 'o'){
                    input >> c;
                    if(input.eof()) throw std::logic_error("Invalid input\n");
                    if(c == 's'){
                        head->value = '&';
                        head->next = std::make_shared<Node<char>>();
                        head->next->value = GetExpr(GetExpr);
                        input >> c;
                        if(input.eof() || c != ')') throw std::logic_error("Invalid input\n");
                        return head;
                    }else throw std::logic_error("Invalid input\n");
                }else if(c == ')'){
                    head->value = 'c';
                    return head;
                } else throw std::logic_error("Invalid input\n");
            case 's':
                input >> c;
                if(input.eof()) throw std::logic_error("Invalid input\n");
                if(c == 'i'){
                    input >> c;
                    if(input.eof()) throw std::logic_error("Invalid input\n");
                    if(c == 'n'){
                        head->value = '$';
                        head->next = std::make_shared<Node<char>>();
                        head->next->value = GetExpr(GetExpr);
                        input >> c;
                        if(input.eof() || c != ')') throw std::logic_error("Invalid input\n");
                        return head;
                    }else throw std::logic_error("Invalid input\n");
                }else if(c == ')'){
                    head->value = 's';
                    return head;
                } else throw std::logic_error("Invalid input\n");
            case ')':
                throw std::logic_error("Invalid input\n");
            default:
                if(isdigit(c)){
                    auto cur = head;
                    head->value = c;
                    while(isdigit(c)){
                        input >> c;
                        if(input.eof()) throw std::logic_error("Invalid input\n");
                        if(!isdigit(c)) break;
                        cur->next = std::make_shared<Node<char>>();
                        cur = cur->next;
                        cur->value = c;
                    }
                    if(c != ')') throw std::logic_error("Invalid input\n");
                    return head;
                }
                if(isalpha(c)){
                    head->value = c;
                    input >> c;
                    if(input.eof()) throw std::logic_error("Invalid input\n");
                    if(c == ')') return head;
                    else throw std::logic_error("Invalid input\n");
                }else throw std::logic_error("Invalid input\n");
        }
    };


    auto DerivedExpr = [&output](std::shared_ptr<Node<char>> head, char var, auto&& DerivedExpr)->void{
        auto PrintExpr = [&output](std::shared_ptr<Node<char>> head, auto&& PrintExpr)->void{
            if(!std::holds_alternative<char>(head->value)) throw std::logic_error("List is broken\n");
            char c = std::get<char>(head->value);
            if(isdigit(c)){
                while(head){
                    output << std::get<char>(head->value);
                    head = head->next;
                }
            } else if(isalpha(c)){
                output << c;
            } else if(head->next->next){
                output << "(";
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), PrintExpr);
                output << ")" << c << "(";
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->next->value), PrintExpr);
                output << ")";
            } else {
                if(c == '$') output << "sin(";
                else if(c == '&') output << "cos(";
                else if(c == '+' || c == '-') output << c << "(";
                else throw std::logic_error("List is broken\n");
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), PrintExpr);
                output << ")";
            }
        };
        if(!std::holds_alternative<char>(head->value)) throw std::logic_error("List is broken\n");
        char c = std::get<char>(head->value);
        if(c == var) output << '1';
        else if(isalpha(c)) output << '0';
        if(isdigit(c)) output << "0";
        switch(c){
            case '+':
            case '-':
                if(head->next->next){
                    output << "(";
                    DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), var, DerivedExpr);
                    output << ")" << c << "(";
                    DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->next->value), var, DerivedExpr);
                    output << ")";
                }else{
                    output << c << "(";
                    DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), var, DerivedExpr);
                    output << ")";
                }
                break;
            case '*':
            case '/':
                output << "((";
                DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), var, DerivedExpr);
                output << ")*(";
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->next->value), PrintExpr);
                if(c == '*') output << ")+(";
                else output << ")-(";
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), PrintExpr);
                output << ")*(";
                DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->next->value), var, DerivedExpr);
                output << "))";
                if(c == '/'){
                    output << "/(";
                    PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->next->value), PrintExpr);
                    output << ")^2";
                }
                break;
            case '&':
            case '$':
                if(c == '&') output << "-sin(";
                else output << "cos(";
                PrintExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), PrintExpr);
                output << ")*(";
                DerivedExpr(std::get<std::shared_ptr<Node<char>>>(head->next->value), var, DerivedExpr);
                output << ")";
        };
    };

    try{
        std::shared_ptr<Node<char>> head = GetExpr(GetExpr);
        if(head == nullptr){
            output << "Error in reading\n";
            return 1;
        }
        char var;
        input >> var;
        if(!isalpha(var)){
            output << "Wrong variable for derived: \'" << var << "\'\n";
            return 1;
        }
        DerivedExpr(head, var, DerivedExpr);
        output << "\n";
    }catch(std::exception& e){
        std::cout << e.what();
        return 1;
    }
    return 0;
}
