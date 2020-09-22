#include<iostream>
#include<fstream>

class ReaderWriter{
private:
    std::ifstream input;
    std::ofstream output;
public:
    ReaderWriter(const char* input_filename, const char* output_filename){
        input.open(input_filename);
        if(!input.is_open()) throw std::runtime_error("Can't open file for input");
        output.open(output_filename);
        if(!output.is_open()) throw std::runtime_error("Can't create/open file for output");
    }
    ~ReaderWriter(){
        input.close();
        output << '\n';
        output.close();
    }
    char GetNextChar(){
        char c;
        input >> c;
        if(IsEOF()) return '\0';
        return c;
    }
    
    char GetAndWriteNextChar(){
        char c;
        input >> c;
        if(IsEOF()) return '\0';
        output << c;
        return c;
    }

    bool IsEOF(){
        return input.eof();
    }

    void WriteChar(char c){
        output << c;
    }

    void WriteString(const char* str){
        output << str;
    }
    
    void WriteString(const std::string& str){
        output << str;
    }
};

class Analyzer{
private:
    ReaderWriter* reader_writer;
    char last_char;
    std::string error_msg;

    bool CheckListParam(){
        ;
        if(CheckParam()){
            char next = reader_writer->GetAndWriteNextChar();
            if(next == ',') return CheckListParam();
            else if(next == ')'){
                last_char = next;
                return true;
            }
            else if(!next) return true;
            error_msg = std::string("List of parameters Error: Expected character \',\', but were given \'") + next + "\'.\n";
            return false;
        }
        return false;
    }
    
    bool CheckParam(){
        ;
        if(CheckName()){
            char next = reader_writer->GetAndWriteNextChar();
            if(next == '='){
                next = reader_writer->GetAndWriteNextChar();
                if(next == '('){
                    if(CheckListParam()){
                        if(last_char == ')'){
                            last_char = 0;
                            return true;
                        }
                        next = reader_writer->GetAndWriteNextChar();
                        if(next == ')') return true;
                        if(next) error_msg = std::string("Parameter Error: Expected character \')\', but were given \'") + next + "\'.\n";
                        else error_msg = "Parameter Error: Expected character \')\', but end of input were reached.\n";
                        return false;
                    }
                    return false;
                }else{
                    if(!(next >= '0' && next <='9')){
                        if(next) error_msg = std::string("Parameter Error: Invalid define, character \'") + next + "\' is not digit.\n";
                        else error_msg = "Parameter Error: Invalid define, expected digit, but end of input were reached.\n";
                        return false;
                    }
                    next = reader_writer->GetAndWriteNextChar();
                    if(!(next >= '0' && next <='9')){
                        if(next) error_msg = std::string("Parameter Error: Invalid define, character \'") + next + "\' is not digit.\n";
                        else error_msg = "Parameter Error: Invalid define, expected digit, but end of input were reached.\n";
                        return false;
                    }
                    return true;
                }
            }
            if(next) error_msg = std::string("Parameter Error: Expected character \'=\', but were given \'") + next + "\'.\n";
            else error_msg = "Parameter Error: Expected character \'=\', but end of input were reached.\n";
            return false;
        }
        return false;
    }
    
    bool CheckName(){
        int count = 0;
        while(count < 3){
            char next = reader_writer->GetAndWriteNextChar();
            if(!(next >= 'A' && next <= 'z')){
                if(next) error_msg = std::string("Name Error: Invalid name, character \'") + next + "\' is not letter.\n";
                else error_msg ="Name Error: Invalid name, excepted letter, but end of input were reached.\n";
                return false;
            }
            count++; 
        }
        return true;
    }
public:
    Analyzer(ReaderWriter* reader_writer){
        this->reader_writer = reader_writer;
        last_char = 0;
    }
    ~Analyzer(){}

    void StartAnalyz(){
        bool correct  = CheckListParam();
        char next = reader_writer->GetNextChar();
        if(last_char != 0 && error_msg.empty()){
            error_msg = std::string("List of parameters Error: Expected character \',\', but were given \'") + last_char + "\'.\n";
            correct = false;
        }
        if(!correct){
            reader_writer->WriteString("\nIncorrect. ");
            reader_writer->WriteString(error_msg);
        }else reader_writer->WriteString("\nCorrect.\n");
    }
};

int main(int argc, char** argv){
    if(argc < 3){
        std::cout << "Usage: param_analyzer /path/to/input /path/to/output\n";
        return 1;
    }
    try{
        ReaderWriter rw(argv[1], argv[2]);
        Analyzer analyzer(&rw);
        analyzer.StartAnalyz();
    }catch(std::exception& e){
        std::cout << e.what() << "\n";
        return 2;
    }
    return 0;
}
