

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
//#define STAT


class Node{
public:
    char c{};
    int count{};
    std::string string;
    std::shared_ptr<Node> left {nullptr};
    std::shared_ptr<Node> right {nullptr};
};

struct Pair{
    std::string symbol;
    std::string code;
};

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

    if (string.size()>0){
        for (char i : string) {
            exist= false;
            for (auto & j : vector) {
                if (i==j->c){
                    exist= true;
                    j->count++;
                }
            }
            if (!exist){
                std::shared_ptr<Node> node;
                node = std::make_shared<Node>();
                node->c=i;
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

std::shared_ptr<Node> cons_tree_huffman(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b){
    std::shared_ptr<Node> head = std::make_shared<Node>();

    head->left=a;
    head->right=b;
    head->count=a->count+b->count;
    head->string=a->string+b->string;

    return head;
}

std::shared_ptr<Node> make_tree_huffman(std::vector<std::shared_ptr<Node>>& vector){
   std::shared_ptr<Node> head;

   while (vector.size() >= 2){

        head= cons_tree_huffman(vector[vector.size() - 1], vector[vector.size() - 2]);
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

void encode(const std::string& string, std::vector<Pair> pairs, const std::string& filename, std::string & res){
    res="";
    std::ofstream file;
    file.open(filename);

    for(char i : string){
        for(auto & pair : pairs){
            if(pair.symbol[0] == i){
                file << pair.code;
                res += pair.code;
            }
        }
    }

    file<<"\n";
    file.close();
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

void cons_fano_tree(std::shared_ptr<Node> &elem, std::vector<std::shared_ptr<Node>> vector) {

    //Condition of end of recursion
    if(vector.size() <= 1) {
        return;
    }

    //Create child Nodes and vectors for them
    std::shared_ptr<Node> right_branch(new Node);
    std::shared_ptr<Node> left_branch(new Node);
    std::vector<std::shared_ptr<Node>> right_cnt_vector;
    std::vector<std::shared_ptr<Node>> left_cnt_vector;

    //Set connection
    elem->right = right_branch;
    elem->left = left_branch;

    //Creating of right branch and vector
    for(size_t i = vector.size() - 1; i >= 1; --i) {

        right_branch->count += vector[i]->count;
        right_branch->string.insert(0, vector[i]->string);
        right_cnt_vector.insert(right_cnt_vector.begin(), vector.back());
        vector.pop_back();

        if(right_branch->count + vector[i - 1]->count >= elem->count / 2) {
            break;
        }
    }

    //Creating of left branch and vector
    left_cnt_vector = vector;
    left_branch->string = elem->string;
    left_branch->string.erase(left_branch->string.end() - right_branch->string.length(), left_branch->string.end());
    left_branch->count = elem->count - right_branch->count;

    //Recursive call
    cons_fano_tree(left_branch, left_cnt_vector);
    cons_fano_tree(right_branch, right_cnt_vector);

}

void make_fano_tree(std::string &input_str, const std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node> &head) {

    int sum = 0;
    std::string all_chars;
    for (const auto & i : vector) {
        sum+=i->count;
        all_chars+=i->c;
    }

    head->count = sum;
    head->string = all_chars;

    cons_fano_tree(head, vector);
}

void read_file(std::vector<std::string> &vector, std::ifstream& ifstream) {
    std::string current_file_string;
    while (std::getline(ifstream, current_file_string))
    {
        if (current_file_string.back() == '\r')
            current_file_string.erase(current_file_string.end() - 1);
        vector.push_back(current_file_string);
    }
}

int stat_process(int argc, char** argv){

    if (argc < 2)
    {
        std::cout << "Incorrect input file\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cout << "Incorrect input file\n";
        return 1;
    }

    std::vector<std::string> file_data;
    read_file(file_data, input);


    std::string string, string2;


    for (auto & i : file_data){
        string+=i;
    }
    string2=string;

    std::shared_ptr<Node> head;
    std::vector<Pair> pairs;
    std::string res_enc_huf;
    std::vector<std::shared_ptr<Node>> vector;
    double start_enc_huffman, end_dec_huffman, start_dec_huffman, start_enc_fano, start_dec_fano, end_enc_fano, end_dec_fano, huffman_enc_time,huffman_dec_time,fano_enc_time, fano_dec_time;


    std::transform(string.begin(), string.end(), string.begin(), tolower);
    if (string.length()<=2){
        std::cout<<"Error: not enough symbols";
        return EXIT_FAILURE;
    }



    //encode
    start_enc_huffman = clock();
    vector= count_symbols(string);
    head = make_tree_huffman(vector);
    make_pairs(head, pairs,"");
    encode(string, pairs, "res_enc_h.txt", res_enc_huf);
    end_dec_huffman=clock();
    huffman_enc_time= (end_dec_huffman - start_enc_huffman) / CLOCKS_PER_SEC;
    std::cout << huffman_enc_time << "\n";

    //decode huffman
    start_dec_huffman=clock();
    decode(res_enc_huf, "res_dec_h.txt", pairs);
    end_dec_huffman =clock();
    huffman_dec_time= (end_dec_huffman - start_dec_huffman) / CLOCKS_PER_SEC;
    std::cout << huffman_dec_time << "\n";

    //Fano encode
    std::shared_ptr<Node> head_fano= std::make_shared<Node>();
    std::string res_enc_fano;
    std::vector<Pair> pairs2;
    start_enc_fano=clock();
    vector= count_symbols(string2);
    make_fano_tree(string2, vector, head_fano);
    make_pairs(head_fano, pairs2,"");
    encode(string2, pairs2, "res_enc_f.txt", res_enc_fano);
    end_enc_fano=clock();
    fano_enc_time=(end_enc_fano-start_enc_fano)/CLOCKS_PER_SEC;
    std::cout<<fano_enc_time<<"\n";

    //decode FANO
    start_dec_fano=clock();
    decode(res_enc_fano, "res_dec_f.txt", pairs2);
    end_dec_fano= clock();
    fano_dec_time=(end_dec_fano-start_dec_fano)/CLOCKS_PER_SEC;
    std::cout<<fano_dec_time<<"\n";

    std::cout<<string.size()<<"\n";
    std::cout << res_enc_huf.size() << "\n";
    std::cout<<res_enc_fano.size()<<"\n";

    return 0;

}

int process(){

    std::string string, string2;

    std::shared_ptr<Node> head;
    std::vector<Pair> pairs;
    std::string res_enc_huf;
    std::vector<std::shared_ptr<Node>> vector;
    double start_enc_huffman, end_dec_huffman, start_dec_huffman, start_enc_fano, start_dec_fano, end_enc_fano, end_dec_fano, huffman_enc_time,huffman_dec_time,fano_enc_time,fano_dec_time;

    std::getline(std::cin, string);

    std::transform(string.begin(), string.end(), string.begin(), tolower);
    if (string.length()<=2){
        std::cout<<"Error: not enough symbols\n";
        return EXIT_FAILURE;
    }
    string2=string;



    //encode huffman
    start_enc_huffman = clock();
    vector= count_symbols(string);
    head = make_tree_huffman(vector);
    make_pairs(head, pairs,"");
    unload_pairs(pairs);
    encode(string, pairs, "res_enc_h.txt", res_enc_huf);
    end_dec_huffman=clock();
    huffman_enc_time= (end_dec_huffman - start_enc_huffman) / CLOCKS_PER_SEC;
    std::cout << "Huffman time encode = " << huffman_enc_time<<" seconds";

    //decode huffman
    start_dec_huffman=clock();
    string = load_from_file("res_enc_h.txt");
    decode(res_enc_huf, "res_dec_h.txt", pairs);
    end_dec_huffman =clock();
    huffman_dec_time= (end_dec_huffman - start_dec_huffman) / CLOCKS_PER_SEC;
    std::cout << "\nHuffman time decode = " << huffman_dec_time<<" seconds";


    //Fano
    std::shared_ptr<Node> head_fano= std::make_shared<Node>();
    std::string res_enc_fano;
    std::vector<Pair> pairs2;
    start_enc_fano=clock();
    vector= count_symbols(string2);
    make_fano_tree(string2, vector, head_fano);
    make_pairs(head_fano, pairs2,"");
    unload_pairs(pairs2,"pairs2.txt");
    encode(string2, pairs2, "res_enc_f.txt", res_enc_fano);
    end_enc_fano=clock();
    fano_enc_time=(end_enc_fano-start_enc_fano)/CLOCKS_PER_SEC;
    std::cout<<"\nFano time encode = "<<fano_enc_time<<" seconds";

    //decode FANO
    start_dec_fano=clock();
    string2 = load_from_file("res_enc_f.txt");
    decode(res_enc_fano, "res_dec_f.txt", pairs2);
    end_dec_fano= clock();
    fano_dec_time=(end_dec_fano-start_dec_fano)/CLOCKS_PER_SEC;
    std::cout<<"\nFano time decode = "<<fano_dec_time<<" seconds";

    std::cout<<"\n____________________________";
    std::cout<<"\nHuffman pairs | ";
    for (auto & pair : pairs) {
        std::cout<<pair.symbol<<" = "<<pair.code<<" | ";
    }
    std::cout<<"\nHuffman code result = ";
    std::cout << res_enc_huf;
    std::cout<<"\n____________________________";

    std::cout<<"\nFano pairs | ";
    for (auto & pair : pairs2) {
        std::cout<<pair.symbol<<" = "<<pair.code<<" | ";
    }
    std::cout<<"\nFano code result = ";
    std::cout<<res_enc_fano;

    std::cout<<"\n____________________________";
    std::cout<<"\nTime difference: \n";
    if (fano_enc_time - huffman_enc_time > 0){
        std::cout<<"Huffman's algorithm is "<< fano_enc_time-huffman_enc_time<<" seconds faster when encoding";
    } else std::cout<<"Fano's algorithm is "<< huffman_enc_time-fano_enc_time<<" seconds faster when encoding";
    std::cout<<"\n";
    if (fano_dec_time - huffman_dec_time > 0){
        std::cout<<"Huffman's algorithm is "<< fano_dec_time-huffman_dec_time<<" seconds faster when decoding";
    } else std::cout<<"Fano's algorithm is "<< huffman_dec_time-fano_dec_time<<" seconds faster when decoding";
    std::cout<<"\n____________________________";
    std::cout<<"\nCompression results: \n";
    if (res_enc_fano.size() - res_enc_huf.size() > 0){
        std::cout<<"Huffman's algorithm compressed better by "<< res_enc_fano.size() - res_enc_huf.size()<<" symbols";
        std::cout<<"\nThis algorithm more efficient by "<<double (double (res_enc_fano.size())/double(res_enc_huf.size()))*100-100<<" percent";
    } else {std::cout<<"Fano's algorithm compressed better by "<< res_enc_huf.size()-res_enc_fano.size()<<" symbols";
        std::cout<<"\nThis algorithm more efficient by "<<double (double (res_enc_huf.size())/double(res_enc_fano.size()))*100-100<<" percent";
        }
    std::cout<<"\n";

    return 0;
}


int main(int argc, char ** argv) {
#ifndef STAT
    return process();
#endif
#ifdef STAT
    return stat_process(argc, argv);
#endif

}

