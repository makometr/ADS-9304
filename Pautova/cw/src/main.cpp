#include <stack>

#include "Research.h"

bool is_correct_object(std::string& object){
    return (object == "height" || object == "time" || object == "t" || object == "h");
}

bool is_corretc_case(std::string& case_str){
    return (case_str == "average" || case_str == "worst" || case_str == "a" || case_str == "w");
}

int main(int argc, char** argv){

    std::string object_of_research;
    std::string what_case;
    std::string info_object("\nWhat do you want to research?\nIf height, then enter \"height\" or \"h\". If search time, then enter \"time\" or \"t\"\nEnter: ");
    std::string info_case("\nWhat case do you want to research?\nIf average, then enter \"average\" or \"a\". If worst, then enter \"worst\" or \"w\"\nEnter: ");
    std::string error_object("\nThe object of research is entered incorrectly\nRe-enter: ");
    std::string error_case("\nThe case of research is entered incorrectly\nRe-enter: ");

    if (argc == 1){
        std::cout << info_object;
        std::getline(std::cin, object_of_research);
        while(!is_correct_object(object_of_research)){
            std::cout << error_object;
            std::getline(std::cin, object_of_research);
        }
        std::cout << info_case;
        std::getline(std::cin, what_case);
        while(!is_corretc_case(what_case)){
            std::cout << error_case;
            std::getline(std::cin, what_case);
        }
    }
    else{
        object_of_research = argv[1];
        while(!is_correct_object(object_of_research)){
            std::cout << error_object;
            std::getline(std::cin, object_of_research);
        }
        what_case = argv[2];
        while(!is_corretc_case(what_case)){
            std::cout << error_case;
            std::getline(std::cin, what_case);
        }
    }
    std::cout << "\nTo see a graph of research results, after the program finishes, enter the command:\n\t";

    Research research;
    if (object_of_research.find("h") != std::string::npos){
        if (what_case.find("a") != std::string::npos){
            std::cout << "\"make plot_height_average\"\n";
            research.research_height(true);
        }
        else{
            std::cout << "\"make plot_height_worst\"\n";
            research.research_height(false);
        }        
    }
    else{
        if (what_case.find("a") != std::string::npos){
            std::cout << "\"make plot_time_average\"\n";
            research.research_time(true);
        }
        else{
            std::cout << "\"make plot_time_worst\"\n";
            research.research_time(false);
        }
    }

    std::cout << "\nThe program is finished\n" <<std::endl;
    return 0;
}