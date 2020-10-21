#include <iostream>
#include <cstdlib>
#include <string>

bool Round(std::string & s, int& iter, int size, std::string & err);

bool Square(std::string & s, int& iter, int size, std::string & err);

bool isBracket(std::string & s);

int main(int argc, char** argv){
    std::string st(argv[1]);
    if(isBracket(st)){
	std::cout << st << '\n';
        std::cout << "It is bracket!" << '\n';
    }
    return 0;
}

bool isBracket(std::string & s){
    std::string err = "";
    int len = s.length();
    int iter = 0;
    err = err + s[iter];
    if(s[0] == '[') {
        iter = iter + 1;
        err = err + s[iter];
        return Square(s, iter, len, err);
    }else if(s[0] == '('){
        iter = iter + 1;
        err = err + s[iter];
        return Round(s, iter, len, err);
    }else{
        std::cout << err << '\n';
        std::cout << "Invalid symbol" << '\n';
        std::cout << "It is not bracket!" << '\n';
        return false;
    }
}

bool Square(std::string & s, int& iter, int size, std::string & err){
    bool res;
    if(iter != size) {
        if (s[iter] == ' ') {
            iter = iter + 1;
            err = err + s[iter];
            if (s[iter] == '[') {
                iter = iter + 1;
                err = err + s[iter];
                if (s[iter] == ' ') {
                    iter = iter + 1;
                    err = err + s[iter];
                    if (s[iter] == 'B') {
                        res = true;
                    } else if (s[iter] == '[') {
                        iter = iter + 1;
                        err = err + s[iter];
                        res = Square(s, iter, size, err);
                    } else {
                        std::cout << err << '\n';
                        std::cout << "Invalid symbol" << '\n';
                        std::cout << "It is not bracket!" << '\n';
                        return false;
                    }
                    iter = iter + 1;
                    err = err + s[iter];
                    if(s[iter] == ' ') {
                        iter = iter + 1;
                        err = err + s[iter];
                        if (s[iter] == ']') {
                            iter = iter + 1;
                            err = err + s[iter];
                            if(s[iter] == ' ') {
                                iter = iter + 1;
                                if (s[iter] == '(') {
                                    iter = iter - 1;
                                    res = Round(s, iter, size, err);
                                } else if (s[iter] == ')') {
                                    return true;
                                } else {
                                    std::cout << err << '\n';
                                    std::cout << "Invalid symbol" << '\n';
                                    std::cout << "It is not bracket!" << '\n';
                                    return false;
                                }
                            }else{
                                std::cout << err << '\n';
                                std::cout << "There must be a probel!" << '\n';
                                std::cout << "It is not bracket!" << '\n';
                                return false;
                            }
                        } else {
                            std::cout << err << '\n';
                            std::cout << "Invalid symbol" << '\n';
                            std::cout << "It is not bracket!" << '\n';
                            return false;
                        }
                    }else{
                        std::cout << err << '\n';
                        std::cout << "There must be a probel!" << '\n';
                        std::cout << "It is not bracket!" << '\n';
                        return false;
                    }
                }else{
                    std::cout << err << '\n';
                    std::cout << "There must be a probel!" << '\n';
                    std::cout << "It is not bracket!" << '\n';
                    return false;
                }
            }else{
                std::cout << err << '\n';
                std::cout << "Invalid symbol" << '\n';
                std::cout << "It is not bracket!" << '\n';
                return false;
            }
        }else{
            std::cout << err << '\n';
            std::cout << "There must be a probel!" << '\n';
            std::cout << "It is not bracket!" << '\n';
            return false;
        }
    }
    return res;
}

bool Round(std::string & s, int& iter, int size, std::string & err){
    bool res;
    if(iter != size) {
        if (s[iter] == ' ') {
            iter = iter + 1;
            err = err + s[iter];
            if (s[iter] == '(') {
                iter = iter + 1;
                err = err + s[iter];
                if (s[iter] == ' ') {
                    iter = iter + 1;
                    err = err + s[iter];
                    if (s[iter] == 'A') {
                        res = true;
                    } else if (s[iter] == '(') {
                        iter = iter + 1;
                        err = err + s[iter];
                        res = Round(s, iter, size, err);
                    } else {
                        std::cout << err << '\n';
                        std::cout << "Invalid symbol" << '\n';
                        std::cout << "It is not bracket!" << '\n';
                        return false;
                    }
                    iter = iter + 1;
                    err = err + s[iter];
                    if(s[iter] == ' ') {
                        iter = iter + 1;
                        err = err + s[iter];
                        if (s[iter] == ')') {
                            iter = iter + 1;
                            err = err + s[iter];
                            if(s[iter] == ' ') {
                                iter = iter + 1;
                                if (s[iter] == '[') {
                                    iter = iter - 1;
                                    res = Square(s, iter, size, err);
                                } else if (s[iter] == ']') {
                                    return true;
                                } else {
                                    std::cout << err << '\n';
                                    std::cout << "Invalid symbol" << '\n';
                                    std::cout << "It is not bracket!" << '\n';
                                    return false;
                                }
                            }else{
                                std::cout << err << '\n';
                                std::cout << "There must be a probel!" << '\n';
                                std::cout << "It is not bracket!" << '\n';
                                return false;
                            }
                        } else {
                            std::cout << err << '\n';
                            std::cout << "Invalid symbol" << '\n';
                            std::cout << "It is not bracket!" << '\n';
                            return false;
                        }
                    }else{
                        std::cout << err << '\n';
                        std::cout << "There must be a probel!" << '\n';
                        std::cout << "It is not bracket!" << '\n';
                        return false;
                    }
                }else{
                    std::cout << err << '\n';
                    std::cout << "There must be a probel!" << '\n';
                    std::cout << "It is not bracket!" << '\n';
                    return false;
                }
            }else{
                std::cout << err << '\n';
                std::cout << "Invalid symbol" << '\n';
                std::cout << "It is not bracket!" << '\n';
                return false;
            }
        }else{
            std::cout << err << '\n';
            std::cout << "There must be a probel!" << '\n';
            std::cout << "It is not bracket!" << '\n';
            return false;
        }
    }
    return res;
}


