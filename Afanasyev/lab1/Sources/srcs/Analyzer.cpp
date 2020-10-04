#include "../libs/Analyzer.h"

Analyzer::Analyzer(const std::string &otherStr, size_t start, size_t end) : str(otherStr), index(start)
{
    lastIndex = (end == std::string::npos) ? otherStr.length() : end;
}

const bool Analyzer::analyzeCnstExpr() // подсчитал линейную скорость o(n)
{
    Object modeNew;
    modeNew.mode = kNothing;
    if (index < lastIndex)
    {
        if (str[index] == '-' || str[index] == '+' || str[index] == '*') // если втречен знак
        {
            if (!(oldMode.mode == kOper || (str[index] == '*' && oldMode.mode == kStart)))
            {
                modeNew.mode = kOper; // в следующем вызове будет информация о том, что была операция
                modeNew.ch = str[index];
                ++index; // шаг на следующий элемент
            }
            else
                return 0; // отрицательный результат, если до этого уже знак был или первым символом в строке встретился *
        }
        else if (str[index] >= '0' && str[index] <= '9') // если цифра
        {
            if (oldMode.mode != kNumber)
            {
                modeNew.mode = kNumber;       // в следующем вызове будет информация о том, что был ряд цифр
                skipSome("1234567890"); // сдвиг индекса к следующему после ряда цифр символу
            }
            else
                return 0; // отрицательный выход, если два ряда цифр подряд
        }
        else if (str[index] == '(') // нахождение скобки
        {
            if (oldMode.mode == kOper || oldMode.mode == kStart)
            {
                long long bar = 1; // переменная, хранящая разницу между между кол-вом открытых и закрытых скобок (bar > 0, когда открытых больше)
                size_t firstIndex = index + 1;
                do
                {
                    ++index;
                    if (str[index] == ')')
                        --bar;
                    else if (str[index] == '(')
                        ++bar;
                } while (bar != 0 && index < lastIndex);

                Analyzer analyzer(str, firstIndex, index);
                if (bar == 0 && analyzer.analyzeCnstExpr() == 1)
                {
                    ++index;                // иначе передвигаем индекс с закрывающей скобки на следующую позицию
                    modeNew.mode = kNumber; // делаем вид, что наши скобки являлись числом, чтобы не было сразу после скобок числа
                }
                else
                    return 0; // отрицатеьлный выход, если кол-во открытых и закрытых скобок не совпало, или, если внутри скобок была обнаружена проблема
            }
            else
                return 0; // отрицательный выход, если перед скобкой было число
        }
        else if (str[index] != ' ' && str[index] != '\t')
            return 0; // отрицательный выход, если встречен неуместный знак

        if (str[index] == ' ' || str[index] == '\t') // игнорирование пробелов
            skipSome(" \t");                   // сдвиг индекса к концу пробелов
    }
    if ((oldMode.mode == kOper || oldMode.mode == kStart) && modeNew.mode == kNothing)
        return 0; // отрицательный выход, если сейчас пусто и раньше пусто (значит строка пуста)
    else if (modeNew.mode == -1 && oldMode.mode >= 0)
        return 1; // положительный выход, если сейчас путо, но раньше что-то было (строка просто закончилась)

    oldMode = modeNew;                  // передаем следующей итерации информацию о нынешней
    return (analyzeCnstExpr()) ? 1 : 0; // рекурсия
}

inline void Analyzer::skipSome(const char *thing)
{
    index = str.find_first_not_of(thing, index + 1); // сдвиг индекса к концу пробелов
    if (index > lastIndex)
        index = lastIndex;
}