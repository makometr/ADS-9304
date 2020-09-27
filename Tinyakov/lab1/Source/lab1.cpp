#include<iostream>
#include<fstream>
#include<string_view>
/* For analyz from string */
// #include<sstream>

class ReaderWriter{
private:
    std::istream& input;
    std::ostream& output;
public:
    ReaderWriter(std::istream& in, std::ostream& out):
    input(in),
    output(out)
    {
    }
    ~ReaderWriter(){
        output << '\n';
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

    void WriteString(std::string_view str){
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
        std::ifstream in(argv[1]);
        std::ofstream out(argv[2]);
        if(!in.is_open()){
            std::cout << "Can't open file " << argv[1] << "\n";
            return 2;
        }
        if(!out.is_open()){
            std::cout << "Can't open/create file " << argv[2] << "\n";
            return 2;
        }
        /* Example with string */
        // std::stringstream in("AAA = 15\n");
        {
            ReaderWriter rw(in, out);
            Analyzer analyzer(&rw);
            analyzer.StartAnalyz();
        }
        in.close();
        out.close();
    }catch(std::exception& e){
        std::cout << e.what() << "\n";
        return 3;
    }
    return 0;
}
