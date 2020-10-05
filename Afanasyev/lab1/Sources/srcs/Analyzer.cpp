#include "../libs/Analyzer.h"

Analyzer::Analyzer(const std::string &otherStr, size_t start, size_t end) : str(otherStr), index(start)
{
    lastIndex = (end == std::string::npos) ? otherStr.length() : end;
    oldObjStatus = kStart;
}

const bool Analyzer::analyzeCnstExpr() // подсчитал линейную скорость o(n)
{
    Status currentObj = kNothing;
    if (index < lastIndex)
    {
        if (str[index] == '-' || str[index] == '+' || str[index] == '*') // если втречен знак
        {
            if (oldObjStatus == kOper || (str[index] == '*' && oldObjStatus == kStart))
                return 0;       // отрицательный результат, если до этого уже знак был или первым символом в строке встретился *
            currentObj = kOper; // в следующем вызове будет информация о том, что была операция
            ++index;            // шаг на следующий элемент
        }
        else if (str[index] >= '0' && str[index] <= '9') // если цифра
        {
            if (oldObjStatus == kNumber)
                return 0;           // отрицательный выход, если два ряда цифр подряд
            currentObj = kNumber;   // в следующем вызове будет информация о том, что был ряд цифр
            skipSome("1234567890"); // сдвиг индекса к следующему после ряда цифр символу
        }
        else if (str[index] == '(') // нахождение скобки
        {
            if (oldObjStatus != kOper && oldObjStatus != kStart)
                return 0;      // отрицательный выход, если перед скобкой было число
            long long bar = 1; // переменная, хранящая разницу между между кол-вом открытых и закрытых скобок (bar > 0, когда открытых больше)
            size_t firstIndex = index + 1;
            do
            {
                ++index;
                if (str[index] == ')') // подсчет скобок
                    --bar;
                else if (str[index] == '(')
                    ++bar;
            } while (bar != 0 && index < lastIndex);

            Analyzer analyzer(str, firstIndex, index);
            if (bar != 0 || analyzer.analyzeCnstExpr() == 0)
                return 0;         // отрицатеьлный выход, если кол-во открытых и закрытых скобок не совпало, или, если внутри скобок была обнаружена проблема
            ++index;              // иначе передвигаем индекс с закрывающей скобки на следующую позицию
            currentObj = kNumber; // делаем вид, что наши скобки являлись числом, чтобы не было сразу после скобок числа
        }
        else if (str[index] != ' ' && str[index] != '\t')
            return 0; // отрицательный выход, если встречен неуместный знак

        if (str[index] == ' ' || str[index] == '\t') // игнорирование пробелов
            skipSome(" \t");                         // сдвиг индекса к концу пробелов
    }
    if ((oldObjStatus == kOper || oldObjStatus == kStart) && currentObj == kNothing)
        return 0; // отрицательный выход, если сейчас пусто и раньше пусто (значит строка пуста)
    else if (currentObj == kNothing && oldObjStatus != kNothing)
        return 1; // положительный выход, если сейчас путо, но раньше что-то было (строка просто закончилась)

    oldObjStatus = currentObj;          // передаем следующей итерации информацию о нынешней
    return (analyzeCnstExpr()) ? 1 : 0; // рекурсия
}

inline void Analyzer::skipSome(const char *thing)
{
    index = str.find_first_not_of(thing, index + 1); // сдвиг индекса на следующий элемент после последовательности символов из thing
    if (index > lastIndex)
        index = lastIndex;
}