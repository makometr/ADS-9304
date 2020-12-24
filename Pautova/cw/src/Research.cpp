#include "Research.h"

void Research::research_height(bool is_average){
    std::string filename;
    if (is_average){
        filename = "results/res_ha.txt";
    }
    else{
        filename = "results/res_hw.txt";
    }
    std::ofstream out(filename);
    if (!out.is_open()){
        std::cout << "not open\n";
        return;
    }
    std::vector<int> sequence{};
    for (int i = 1; i <= 30; i++){
        if (is_average){
            sequence = this->generate_randomseq(i);
        }
        else{
            sequence = this->generate_sequence(i);
        }

        std::shared_ptr<BinTree<int>> ibst = std::make_shared<BinTree<int>>(sequence);
        std::shared_ptr<BST> bst = std::make_shared<BST>(sequence);

        out << sequence.size() << ' ' << ibst->height(ibst->get_head()) << ' ' << bst->height(bst->get_head()) << '\n';

        sequence.clear();
    }

    out.close();
}

void Research::research_time(bool is_average){
    srand(time(NULL));
    std::string filename;
    if (is_average){
        filename = "results/res_ta.txt";
    }
    else{
        filename = "results/res_tw.txt";
    }
    std::ofstream out(filename);
    if (!out.is_open()){
        std::cout << "not open\n";
        return;
    }
    std::vector<int> sequence{};
    int elem_to_find;
    std::map<int, int> map;

    for (int i = 1000; i <= 10000;){
        if (is_average){
            sequence = this->generate_randomseq(i);
            elem_to_find = sequence[rand()%(i/2)+100];
            i += 50;
        }
        else{
            sequence = this->generate_sequence(i);
            elem_to_find = sequence[i/2];
            i += 100;
        }

        std::shared_ptr<BinTree<int>> ibst = std::make_shared<BinTree<int>>(sequence);
        ibst->set_E(elem_to_find);
        std::shared_ptr<BST> bst = std::make_shared<BST>(sequence);
        bst->set_E(elem_to_find);
        for (int i = 0; i < (int)sequence.size(); i++){
            map[i] = sequence[i];
        }

        auto start_find_in_ibst = std::chrono::steady_clock::now();
        ibst->find(elem_to_find);
        auto end_find_in_ibst = std::chrono::steady_clock::now();

        auto start_find_in_bst = std::chrono::steady_clock::now();
        bst->find(elem_to_find);
        auto end_find_in_bst = std::chrono::steady_clock::now();

        auto start_find_in_map = std::chrono::steady_clock::now();
        map.find(elem_to_find);
        auto end_find_in_map = std::chrono::steady_clock::now();

        auto find_in_ibst_mks = std::chrono::duration_cast<std::chrono::microseconds>(end_find_in_ibst-start_find_in_ibst);
        auto find_in_bst_mks = std::chrono::duration_cast<std::chrono::microseconds>(end_find_in_bst-start_find_in_bst);
        auto find_in_map_mks = std::chrono::duration_cast<std::chrono::microseconds>(end_find_in_map-start_find_in_map);

        out << sequence.size() << ' ';
        out << find_in_ibst_mks.count() << ' ';
        out << find_in_bst_mks.count() << ' ';
        out << find_in_map_mks.count() << '\n';

        sequence.clear();
        map.clear();
    }

    out.close();
}

std::vector<int> Research::generate_sequence(int size){
    std::vector<int> sequence{};
    for (int i = 1; i<= size; i++){
        sequence.push_back(i);
    }
    return sequence;
}

std::vector<int> Research::generate_randomseq(int size){
    srand(time(NULL));
    std::vector<int> random_sequence{};
    for (int i = 1; i<= size; i++){
        random_sequence.push_back(i);
    }
    int end_swap;
    if (size < 1000){
        end_swap = size;
    }
    else{
        end_swap = size/10;
    }
    for(int j = 0; j <= end_swap; j++){
        int first = rand()%size;
        int second = first + rand()%(size-first);
        std::swap(random_sequence[first], random_sequence[second]);
    }
    return random_sequence;
}