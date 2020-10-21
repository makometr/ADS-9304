#include <iostream>

using namespace std;

bool round_brackets(int &index, string &str, string &result);
bool braces (int &index, string &str, string &result);
bool square_brackets(int &index, string &str, string &result);
bool bracketed_text(string &str, string &result);

bool braces (int &index, string &str, string &result){
    bool k;
    result += str[index];
    index++;
    while (str[index] != '}'){
        if ((str[index] == 'A' || str[index] == 'B') && (str[index - 1] == '{' || str[index - 1] == ' ')){
            result += str[index];
        }

        else if (str[index] == ' ' && (str[index - 1] == 'A' || str[index - 1] == 'B' || str[index - 1] == '}' || str[index - 1] == ']' || str[index - 1] == ')')){
            result += str[index];
        }

        else if (str[index] == '{' && (str[index - 1] == '{' || str[index - 1] == ' ')){
            k = braces(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '(' && (str[index - 1] == '{' || str[index - 1] == ' ')){
            k = round_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '[' && (str[index - 1] == '{' || str[index - 1] == ' ')){
            k = square_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else {
            result += str[index];
            if (str[index] == 'A' || str[index] == 'B' || str[index] == '{' || str[index] == '(' || str[index] == '['){
                cout << "Error: space expected!\n";
            }

            else if (str[index] == ' '){
                cout << "Error: odd space!\n";
            }

            else if (str[index] == ']' || str[index] == ')'){
                cout << "Error: wrong type of closing brackets!\n";
            }

            else if (index == str.length()){
                cout << "Error: missing closing brackets!\n";
            }

            else {
                cout << "Error: invalid character!\n";
            }

            return false;
        }

        index++;
    }

    if(str[index - 1] != '{' && str[index - 1] != ' '){
        result += str[index];
        return true;
    } else {
        result += str[index];
        cout << "Error: the contents of the brackets must not be empty or end with a space!\n";
        return false;
    }
}


bool round_brackets(int &index, string &str, string &result){
    bool k;
    result += str[index];
    index++;
    while (str[index] != ')'){
        if ((str[index] == 'A' || str[index] == 'B') && (str[index - 1] == '(' || str[index - 1] == ' ')){
            result += str[index];
        }

        else if (str[index] == ' ' && (str[index - 1] == 'A' || str[index - 1] == 'B' || str[index - 1] == '}' || str[index - 1] == ']' || str[index - 1] == ')')){
            result += str[index];
        }

        else if (str[index] == '(' && (str[index - 1] == '(' || str[index - 1] == ' ')){
            k = round_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '{' && (str[index - 1] == '(' || str[index - 1] == ' ')){
            k = braces(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '[' && (str[index - 1] == '(' || str[index - 1] == ' ')){
            k = square_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else {
            result += str[index];
            if (str[index] == 'A' || str[index] == 'B' || str[index] == '{' || str[index] == '(' || str[index] == '['){
                cout << "Error: space expected!\n";
            }

            else if (str[index] == ' '){
                cout << "Error: odd space!\n";
            }

            else if (str[index] == '}' || str[index] == ']'){
                cout << "Error: wrong type of closing brackets!\n";
            }

            else if (index == str.length()){
                cout << "Error: missing closing brackets!\n";
            }

            else {
                cout << "Error: invalid character!\n";
            }

            return false;
        }

        index++;
    }

    if(str[index - 1] != '(' && str[index - 1] != ' '){
        result += str[index];
        return true;
    } else {
        result += str[index];
        cout << "Error: the contents of the brackets must not be empty or end with a space!\n";
        return false;
    }
}



bool square_brackets(int &index, string &str, string &result){
    bool k;
    result += str[index];
    index++;
    while (str[index] != ']'){
        if ((str[index] == 'A' || str[index] == 'B') && (str[index - 1] == '[' || str[index - 1] == ' ')){
            result += str[index];
        }

        else if (str[index] == ' ' && (str[index - 1] == 'A' || str[index - 1] == 'B' || str[index - 1] == '}' || str[index - 1] == ']' || str[index - 1] == ')')){
            result += str[index];
        }

        else if (str[index] == '[' && (str[index - 1] == '[' || str[index - 1] == ' ')){
            k = square_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '{' && (str[index - 1] == '[' || str[index - 1] == ' ')){
            k = braces(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str[index] == '(' && (str[index - 1] == '[' || str[index - 1] == ' ')){
            k = round_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else {
            result += str[index];
            if (str[index] == 'A' || str[index] == 'B' || str[index] == '{' || str[index] == '(' || str[index] == '['){
                cout << "Error: space expected!\n";
            }

            else if (str[index] == ' '){
                cout << "Error: odd space!\n";
            }

            else if (str[index] == '}' || str[index] == ')'){
                cout << "Error: wrong type of closing brackets!\n";
            }

            else if (index == str.length()){
                cout << "Error: missing closing brackets!\n";
            }

            else {
                cout << "Error: invalid character!\n";
            }

            return false;
        }

        index++;
    }



    if(str[index - 1] != '[' && str[index - 1] != ' '){
        result += str[index];
        return true;
    } else {
        result += str[index];
        cout << "Error: the contents of the brackets must not be empty or end with a space!\n";
        return false;
    }
}

bool bracketed_text(string &str, string &result){
    int index = 0;
    bool k;
    if (index == str.length()){
        cout << "Error: string must be init";
        return false;
    }

    while (index < str.length()){
        if (str [index] == '{' && (str[index - 1] == ' ' || index == 0)){
            k = braces(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str [index] == '(' && (str[index - 1] == ' ' || index == 0)){
            k = round_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else if (str [index] == '[' && (str[index - 1] == ' ' || index == 0)){
            k = square_brackets(index, str, result);
            if (!k){
                return false;
            }
        }

        else if ((str[index] == 'A' || str[index] == 'B') && (str[index - 1] == '[' || str[index - 1] == ' ' || index == 0)){
            result += str[index];
        }

        else if (str[index] == ' ' && (str[index - 1] == 'A' || str[index - 1] == 'B' || str[index - 1] == '}' || str[index - 1] == ']' || str[index - 1] == ')') && (index + 1) != str.length()){
            result += str[index];
        }

        else {
            result += str[index];
            if (str[index] == 'A' || str[index] == 'B' || str[index] == '{' || str[index] == '(' || str[index] == '['){
                cout << "Error: space expected!\n";
            }

            else if (str[index] == ' '){
                cout << "Error: odd space!\n";
            }

            else {
                cout << "Error: invalid character!\n";
            }

            return false;

        }
        index++;
    }

    return true;
}

int main(int argc, char **argv) {
    string result;
    string str(argv[1]);
    if (bracketed_text(str, result)){
        cout << "Oh, YES, it's bracketed_text\n" << result;
    } else {
        cout << result;
    }
    return 0;
}

