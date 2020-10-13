#include "../libs/MyList.h"

MyList::MyList(const std::string_view &&str)
{
    bool isFirstBar = 1;
    size_t index = 0;
    while (index < str.length())
    {
        if (str[index] == '(')
        {
            size_t leftIndex = index;
            long long bar = 0;
            do
            {
                if (str[index] == '(')
                    --bar;
                else if (str[index] == ')')
                    ++bar;
                ++index;
            } while (bar != 0 && index < str.length());
            if (bar != 0)
                throw MyException(ExceptionsNames::ex_list_is_wrong);
            if (isFirstBar == 1)
            {
                isFirstBar = 0;
                index = leftIndex + 1;
            }
            else
            {
                std::shared_ptr<MyList> newItem(new MyList(str.substr(leftIndex, index - leftIndex)));
                Node newNode;
                newNode.item = newItem;
                this->append(newNode);
            }
        }
        else if (str[index] >= 'A' && str[index] <= 'Z' || str[index] >= 'a' && str[index] <= 'z' || str[index] >= '0' && str[index] <= '9' || str[index] == '-')
        {
            size_t leftIndex = index;
            index = str.find_first_not_of("0123456789QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm-", index + 1);
            const std::string_view newItem = str.substr(leftIndex, index - leftIndex);
            Node newNode;
            newNode.item = (std::string)newItem;
            this->append(newNode);
        }
        else if (str[index] == ' ' || str[index] == '\t' || str[index] == ')')
            ++index;
        else
            throw MyException(ExceptionsNames::ex_list_is_wrong);
    }
}

void MyList::append(const Node &newNode)
{
    std::shared_ptr<Node> node = std::make_shared<Node>(newNode);
    std::shared_ptr<Node> ptr = this->head;
    if (this->head != nullptr)
    {
        while (ptr->next != nullptr)
            ptr = ptr->next;
        ptr->next = node;
    }
    else
        this->head = node;
}

const bool MyList::isNum(const std::string_view &str)
{
    size_t i = 0;
    if (str[0] == '-')
        i = 1;
    for (; i < str.length(); ++i)
        if (!std::isdigit(str[i]))
            return 0;
    return 1;
}

const bool MyList::calculateLogicExpr(const MyList &listOfValues)
{
    try
    {
        return MyList::calculate(this->head, listOfValues, CheckArgumentFlag::Start);
    }
    catch (const MyException &ex)
    {
        std::cout << ex << '\n';
        return 0;
    }
}

const bool MyList::calculate(std::shared_ptr<Node> ptrNode, const MyList &listOfValues, const CheckArgumentFlag check)
{
    if (ptrNode == nullptr)
        throw MyException(ExceptionsNames::ex_expr_is_wrong);
    if (check == CheckArgumentFlag::NextIsArg && ptrNode->next == nullptr)
        throw MyException(ExceptionsNames::ex_argument_doesnt_exists);
    if (check == CheckArgumentFlag::NextIsNothing && ptrNode->next != nullptr)
        throw MyException(ExceptionsNames::ex_unnecessary_argument);

    else if (std::holds_alternative<std::string>(ptrNode->item))
    {
        std::string str = std::get<std::string>(ptrNode->item);
        if (str == "NOT")
            return !MyList::calculate(ptrNode->next, listOfValues, CheckArgumentFlag::NextIsNothing);
        else if (str == "OR")
        {
            const bool left = MyList::calculate(ptrNode->next, listOfValues, CheckArgumentFlag::NextIsArg);
            const bool right = MyList::calculate(ptrNode->next->next, listOfValues, CheckArgumentFlag::NextIsNothing);
            return left || right;
        }
        else if (str == "XOR")
        {
            const bool left = MyList::calculate(ptrNode->next, listOfValues, CheckArgumentFlag::NextIsArg);
            const bool right = MyList::calculate(ptrNode->next->next, listOfValues, CheckArgumentFlag::NextIsNothing);
            return !left && right || left && !right;
        }
        else if (str == "AND")
        {
            const bool left = MyList::calculate(ptrNode->next, listOfValues, CheckArgumentFlag::NextIsArg);
            const bool right = MyList::calculate(ptrNode->next->next, listOfValues, CheckArgumentFlag::NextIsNothing);
            return left && right;
        }
        else
        {
            if (check == CheckArgumentFlag::Start && ptrNode->next != nullptr)
                throw MyException(ExceptionsNames::ex_unnecessary_argument);
            if (isNum(str))
                return std::stoll(str);
            else if (str == "true" || str == "TRUE")
                return 1;
            else if (str == "false" || str == "FALSE")
                return 0;
            else
                return findValue(str, listOfValues);
        }
    }
    else
        return MyList::calculate(std::get<std::shared_ptr<MyList>>(ptrNode->item)->head, listOfValues, CheckArgumentFlag::Start);
}

const long long MyList::findValue(const std::string_view &aim, const MyList &list)
{
    if (list.head == nullptr)
        throw MyException(ExceptionsNames::ex_empty_values_list);
    std::shared_ptr<Node> ptr = list.head;
    while (ptr != nullptr)
    {
        if (!std::holds_alternative<std::shared_ptr<MyList>>(ptr->item))
            throw MyException(ExceptionsNames::ex_incorrect_values_list);

        std::shared_ptr<MyList> ptrList = std::get<std::shared_ptr<MyList>>(ptr->item);
        if (ptrList->head == nullptr || ptrList->head->next == nullptr || !std::holds_alternative<std::string>(ptrList->head->item) || !std::holds_alternative<std::string>(ptrList->head->next->item) || ptrList->head->next->next != nullptr)
            throw MyException(ExceptionsNames::ex_incorrect_values_list);

        if (aim == std::get<std::string>(ptrList->head->item))
        {
            std::string rightStr = std::get<std::string>(ptrList->head->next->item);
            if (rightStr == "TRUE" || rightStr == "true")
                return 1;
            else if (rightStr == "FALSE" || rightStr == "false")
                return 0;
            else if (isNum(rightStr))
                return std::stoll(rightStr);
            else
                throw MyException(ExceptionsNames::ex_incorrect_values_list);
        }
        ptr = ptr->next;
    }
    throw MyException(ExceptionsNames::ex_the_value_of_the_variable_is_missing);
}