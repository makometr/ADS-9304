#include <iostream>
#include <fstream>
#include <string>


/*
    Все 3 функции принимают на вход:
    - Ссылку на строку с нашими данными
    - Позицию открывающей скобы в массиве
    - Ссылку на позицию итератора
*/

void is_circle(std::string&, size_t, size_t&);    
void is_square(std::string&, size_t, size_t&);
void is_figured(std::string&, size_t, size_t&);



int main(int argc, char* argv[])
{

    setlocale(LC_ALL, "ru");  // Рашен лангуаге

    if(argc != 2)   // Проверка кол-ва аргументов у программы
    {
        std::cout << "Неверное кол-во аргументов!\n";
    }

    std::ifstream test(argv[1]);    // Файл на чтение

    if(!test)
    {
        std::cout << "Файл " << argv[1] << " не может быть открыт на чтение!\n"; 
    }

    std::string myString;
    std::getline(test, myString);   // Получаем в строку myString данные из файла

/*
    Проверка корректности входных данных
*/

    size_t open = 0;
    size_t close = 0;

    for(int i = 0; i < myString.size(); i++){
        if(!(myString[i] == '(' || myString[i] == '[' || myString[i] == '{' ||
             myString[i] == ')' || myString[i] == ']' || myString[i] == '}' ||
             myString[i] == '+' || myString[i] == '-' || myString[i] == '0'))
        {
            std::cout << "Некорректные символы в строке!" << std::endl;
            return 0;
        }
        if(myString[i] == '(' || myString[i] == '[' || myString[i] == '{'){
            open++;
        }
        if(myString[i] == ')' || myString[i] == ']' || myString[i] == '}'){
            close++;
        }
    }

    if(open != close){
        std::cout << "Кол-во открывающих скоробок не совпадает с закрывающими!" << std::endl;
        return 0;
    }

    std::cout << myString << " <- Начальная строка\n";

    size_t second = 0;

    if(myString[second] == '('){
        is_circle(myString, second, second);
    }else if(myString[second] == '['){
        is_square(myString, second, second);
    }else if(myString[second] == '{'){
        is_figured(myString, second, second);
    }else{
        std::cout << "Кривое начало строки!" << std::endl;
        return 0;
    }

   std::cout << myString << " <-ЭТО СКОБКИ!" << std::endl;


    return 0;
}



void is_square(std::string &s, size_t first, size_t &second)
{
    std::cout << "Открылись квадратные скобки!\n";
    //std::cout << "Открылись квадратные скобки!\n\tfirst = " << s[first] << "\n\tsecond = " << s[second+1] << '\n';

    second++;

    for(int i = 0; i < second; i++){
        std::cout << s[i];
    }
    std::cout << '\n';

    if(s[second] == ']'){
        if(s[first] == '[' && second - first == 1){
            std::cout << "Не хватает -" << std::endl;
            exit(1);
        }
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }
    
    if(s[first] == '+' && s[second] == '-'){
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }else{
        if(s[second] == '-'){
            is_circle(s, second, second);
        }else{
            if(s[second] == '('){
                is_circle(s, second, second);
                if(s[second] == '{'){
                    is_figured(s, second, second);
                }else if(s[first] == '+'){
                    std::cout << "\tЗакрылись скобки " << s[first] << ' ' << "()" << '\n';
                    return; 
                }else{
                    std::cout << "Не хватает {" << std::endl;
                    exit(1);
                }
            }else{
                std::cout << "Не хватает ( или -" << std::endl;
                exit(1);
            }
        }
        second--;
        is_square(s, first, second);
    }
}



void is_circle(std::string &s, size_t first, size_t &second)
{
    std::cout << "Открылись круглые скобки!\n";
    
    second++;

    for(int i = 0; i < second; i++){
        std::cout << s[i];
    }
    std::cout << '\n';

    if(s[second] == ')'){
        if(s[first] == '(' && second - first == 1){
            std::cout << "Не хватает 0" << std::endl;
            exit(1);
        }
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }
    
    if(s[first] == '-' && s[second] == '0'){
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }else{
        if(s[second] == '0'){
            is_figured(s, second, second);
        }else{
            if(s[second] == '{'){
                is_figured(s, second, second);
                if(s[second] == '['){
                    is_square(s, second, second);
                }else if(s[first] == '-'){
                    std::cout << "\tЗакрылись скобки " << s[first] << ' ' << "{}" << '\n';
                    return; 
                }else{
                    std::cout << "Не хватает [" << std::endl;
                    exit(1);
                }
            }else{
                std::cout << "Не хватает { или 0" << std::endl;
                exit(1);
            }
        }
        second--;
        is_circle(s, first, second);
    }
}



void is_figured(std::string &s, size_t first, size_t &second)
{
    std::cout << "Открылись фигурные скобки!\n";

    second++;

    for(int i = 0; i < second; i++){
        std::cout << s[i];
    }
    std::cout << '\n';

    if(s[second] == '}'){
        if(s[first] == '{' && second - first == 1){
            std::cout << "Не хватает +" << std::endl;
            exit(1);
        }
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }
    
    if(s[first] == '0' && s[second] == '+'){
        std::cout << "\tЗакрылись скобки " << s[first] << ' ' << s[second] << '\n';
        second++;
        return;
    }else{
        if(s[second] == '+'){
            is_square(s, second, second);
        }else{
            if(s[second] == '['){
                is_square(s, second, second);
                if(s[second] == '('){
                    is_circle(s, second, second);
                }else if(s[first] == '0'){
                    std::cout << "\tЗакрылись скобки " << s[first] << ' ' << "[]" << '\n';
                    return;
                }else{
                    std::cout << "Не хватает (" << std::endl;
                    exit(1);
                }
            }else{
                std::cout << "Не хватает [ или +" << std::endl;
                exit(1);
            }
        }
        second--;
        is_figured(s, first, second);
    }
}