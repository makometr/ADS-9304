#include <iostream>
#include <memory>
#include <string>
#include <getopt.h>
#include <fstream>
#include <vector>
#include <algorithm>


class Node{
public:
    char c{};
    int count{};
    std::string string;
    std::shared_ptr<Node> left {nullptr};
    std::shared_ptr<Node> right {nullptr};

};

struct Config{

    int encode;
    int decode;
    std::string pairs;
    int debug;
    int from_file;
    std::string ifile;
    std::string ofile;
};

struct Pair{
    std::string symbol;
    std::string code;
};


void print_help(){
    std::cout<<"to encode: -e -f input_file\nto decode: -d pairs_file -f binary_file [-o <file_name> to save output]\n";
}

std::string load_from_file(const std::string& filename){
    std::string data;
    std::string string;
    std::ifstream file;
    file.open(filename);
    while(getline(file, string)){
        data+=string;
    }
    file.close();
    return data;
}

void print_vector(const std::vector<std::shared_ptr<Node>>& vector)
{
    for (auto & i : vector) {
        std::cout<<i->string<<"="<<i->count<<" ";
    }
    std::cout<<"\n";
}
void printTree(std::shared_ptr<Node> node, int n =0 ){
    if (node!= nullptr) {
        std::cout << ' ' << node->string<<"="<<node->count;
        if(node->right!= nullptr) {
            printTree (node->right,n+1);
        }
        else std::cout <<"\n";

        if(node->left!= nullptr) {
            for (int i=1;i<=n;i++){
                std::cout << "  ";
            }
            printTree (node->left,n+1);
        }
    }
    else {
        std::cout<<"Tree is empty!";
    }
}

bool comp(std::shared_ptr<Node> &left, std::shared_ptr<Node> &right){
    return left->count > right->count;
}

std::vector<std::shared_ptr<Node>> count_symbols(const std::string& string){
    std::vector<std::shared_ptr<Node>> vector;

    bool exist;

    if (string.size()>1){
        for (int i = 1; i < string.size(); ++i) {
            exist= false;
            for (auto & j : vector) {
                if (string[i]==j->c){
                    exist= true;
                    j->count++;
                }
            }
            if (!exist){
                std::shared_ptr<Node> node;
                node = std::make_shared<Node>();
                node->c=string[i];
                node->count=1;
                    vector.push_back(node);
            }
        }
    }
    for (auto & i : vector) {
        i->string=i->c;
    }
    std::sort(vector.begin(), vector.end(),comp);
    //print_vector(vector);
    return vector;
}

std::shared_ptr<Node> consTree(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b){
    std::shared_ptr<Node> head = std::make_shared<Node>();

    head->left=a;
    head->right=b;
    head->count=a->count+b->count;
    head->string=a->string+b->string;

    return head;
}

std::shared_ptr<Node> make_tree( std::vector<std::shared_ptr<Node>>& vector){
   std::shared_ptr<Node> head;

   while (vector.size() >= 2){

        head=consTree(vector[vector.size()-1], vector[vector.size()-2]);
        vector.pop_back();
        vector.pop_back();
        vector.push_back(head);
        std::sort(vector.begin(), vector.end(), comp);

   }

    return head;
}

void make_pairs( std::shared_ptr<Node>& head, std::vector<Pair>& pairs,std::string string){

    if(head->left == nullptr &&  head->right == nullptr){
        pairs.push_back({head->string, string});
    }
    if(head->left != nullptr) {
        make_pairs(head->left, pairs, string + "0");
    }
    if(head->right != nullptr) {
        make_pairs(head->right, pairs, string + "1");
    }
}
void unload_pairs(const std::vector<Pair>& pairs, const std::string& filename= "pairs.txt"){
    std::ofstream file;
    file.open(filename);
    for(auto & pair : pairs){
        file<<pair.symbol<<" - "<< pair.code <<"\n";
    }
    file.close();
}

void encode(const std::string string, std::vector<Pair> pairs, std::string filename){
    std::ofstream file;
    file.open(filename);
    for(char i : string){
        for(auto & pair : pairs){
            if(pair.symbol[0] == i)
                file << pair.code;
        }
    }
    file<<"\n";
    file.close();
}

std::vector<Pair> read_pairs(const std::string& filename){
    std::vector<Pair> vector;
    std::ifstream file(filename);
    std::string string;
    std::string symbol;
    std::string code;
    while(getline(file, string, '\n')){
        code.clear();
        symbol = string[0];
        for(int i = 4; i < string.size(); ++i){
            code.push_back(string[i]);
        }
        vector.push_back({symbol, code});
    }
    return vector;
}
void decode(std::string encodedText, const std::string& decoded, const std::vector<Pair>& codes){
    std::ofstream file;
    file.open(decoded);
    std::string code;
    std::string::iterator iterator = encodedText.begin();
    while(encodedText.end() != iterator){
        code += *iterator;
        for(auto & i : codes){
            if(i.code == code){
                file << i.symbol;
                code.clear();
            }
        }
        iterator++;
    }
    file << "\n";
    file.close();
}


void process(const Config& config, int argc , char** argv){

    if (config.encode !=1 && config.decode != 1){
        std::cout<<"Error: incorrect input\n";
        return;
    }
    std::string string;
    if (config.from_file==0){
        if (argc!=0) {
            string = argv[0];
        } else {
            std::cout<<"Error: incorrect input\n";
            return;
        }
    }
    if (config.from_file==1){
        string = load_from_file(config.ifile);
    }

    if (config.encode==1){
        std::vector<std::shared_ptr<Node>> vector;
        vector= count_symbols(string);
        std::shared_ptr<Node> head;
        head = make_tree(vector);
        std::vector<Pair> pairs;
        make_pairs(head, pairs,"");
        unload_pairs(pairs);
        encode(string,pairs,config.ofile);
    }
    if (config.decode==1){
        string = load_from_file(config.ifile);
        std::vector<Pair> pairs = read_pairs(config.pairs);
        decode(string,config.ofile, pairs);
    }

}


int main(int argc, char ** argv) {


    char options[] = "ed:Df:o:h";
    struct option longopts[] = {
            { "encode", no_argument, nullptr, 'e' },
            { "decode", required_argument, nullptr, 'd'},
            { "help", no_argument, nullptr, 'h' },
            {"debug",no_argument, nullptr, 'D'},
            { "file", required_argument, nullptr, 'f' },
            { "output", required_argument, nullptr, 'o' },

            { nullptr, 0, nullptr, 0 }
    };
    Config config = {
            0,			// encode
            0,          //decode
            "",
            0,          // debug
            0,			// from_file

            "",		// ifile
            "out.txt",		// ofile

    };

    int opt;
    int longidx;


    while (true)
    {
        opt = getopt_long(argc, argv, options, longopts, &longidx);
        if (opt == -1)
            break;

        switch (opt)
        {
            case 'e':
                config.encode=1;
//                std::cout<<"=encode\n";
                break;

            case 'h':
                print_help();

                return 0;

            case 'd':
                config.decode=1;
                config.pairs=optarg;
//                std::cout<<"=decode\n";
                break;

            case 'f':
                config.ifile = optarg;
                config.from_file=1;
//                std::cout<<"=infile\t"<<optarg<<"\n";
                break;

            case 'o':
                config.ofile = optarg;
//                std::cout<<"=outfile\t"<<optarg<<"\n";
                break;

            case 'D':
                config.debug=1;
//                std::cout<<"=DEBUG\n";
                break;
            default:
                break;
        }
    }
    argc -= optind;
    argv += optind;

    process(config,argc,argv);

    return 0;
}

