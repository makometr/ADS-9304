#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <regex>

template<typename type>
std::ostream &operator << (std::ostream &out, const std::vector<type> &arr) {
    if (arr.size() == 0) {
        out << "[]";
    } else {
        out << '[';
        for (int i = 0; i < arr.size() - 1; i++)
            out << arr[i] << ", ";
        out << arr[arr.size() - 1] << ']';
    }
    return out;
}

template<typename type>
void patienceSort (std::vector<type> &array) {
    std::vector<std::stack<type>> arrStack;
    int size = 0;
    int count = array.size();
    bool isStart = false;

    // first stage
    for (type elem : array) {
        if (!isStart) {
            std::stack<type> stack;
            arrStack.push_back(stack);
            arrStack[0].push(elem);
            size++;
            isStart = true;
            continue;
        }
        bool flag = false;
        for (int i = 0; i < size; i++) {
            if (arrStack[i].top() >= elem) {
                arrStack[i].push(elem);
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::stack<type> stack;
            arrStack.push_back(stack);
            arrStack[size].push(elem);
            size++;
        }
    }

    array.clear();
    std::cout << '\t' << array << '\n';

    // second stage
    std::stack<type> queue;
    for (int i = size - 1; i >= 0; i--) {
        queue.push(arrStack[i].top());
        arrStack[i].pop();
    }
    int queueCount = size;
    for (int k = 0; k < count; k++) {
        array.push_back(queue.top());
        queue.pop();
        std::cout << '\t' << array << '\n';
        queueCount--;
        if (k == count - 1)
            break;
        type min;
        int numStack;
        if (queue.empty()) {
            for (int i = 0; i < size; i++) {
                if (!arrStack[i].empty()) {
                    min = arrStack[i].top();
                    numStack = i;
                    break;
                }
            }
        } else {
            min = queue.top();
            numStack = -1;
        }
        for (int i = 0; i < size - queueCount; i++) {
            if (!arrStack[i].empty() && arrStack[i].top() < min) {
                min = arrStack[i].top();
                numStack = i;
            }
        }
        if (numStack > -1) {
            queue.push(arrStack[numStack].top());
            queueCount++;
            arrStack[numStack].pop();
        }
    }
}

bool checkString (std::string &str) {
    std::regex target("( )+");
    str = std::regex_replace(str, target, " ");
    if (str[0] == ' ')
        str.erase(0, 1);
    if (str[str.size() - 1] == ' ')
        str.erase(str.size() - 1, 1);
    if (str.size() == 0)
        return false;
    return true;
}

int main (int argc, char **argv) {
    std::vector<int> array;
    std::string input;
    if (argc < 2)
        std::getline(std::cin, input);
    else
        input = argv[1];
    if (!checkString(input)) {
        std::cout << "Error: wrong input string\n";
        return 0;
    }
    std::istringstream stream(input);
    int data;
    while (stream >> data)
        array.push_back(data);
    if (array.empty()) {
        std::cout << "Error: wrong input string\n";
        return 0;
    }
    std::cout << "Input array: " << array << '\n';
    std::vector<int> copyArray = array;
    std::sort(copyArray.begin(), copyArray.end());
    patienceSort<int>(array);
    std::cout << "Array sorted with patience sort: " << array << '\n';
    std::cout << "Array sorted with std::sort: " << copyArray << '\n';
    return 0;
}
