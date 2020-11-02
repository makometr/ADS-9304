#include "Algorithm.h"

void Algorithm::StartDataProcessing()
{
	Algorithm algorithm;

	std::list<std::string> input_data = algorithm.InputData();
	
	std::ofstream output("./Tests/output.txt");
	
	while (input_data.size() != 0) {

		std::size_t t = input_data.front().find("Testing the");
		if (t == 0) {
			output << '\n';
			output << input_data.front() << "\n\n";
			input_data.pop_front();
			continue;
		}
		else {
			if (input_data.front()[0] == '(' && input_data.front()[1] != ')') {
				int position = 1;
				std::shared_ptr<HierarchicalList> h_list = HierarchicalList::CreateHList(input_data.front(), position);
			
				if (output.is_open()) {
					if (algorithm.IsCorrect(h_list)) {
						output << input_data.front() << " - CORRECT!" << '\n';
					}
					else {
						output << input_data.front() << " - INCORRECT!" << '\n';
					}
					input_data.pop_front();
				}
				else {
					std::cout << "Can't open output file!" << std::endl;
				}
			}
			else {
				output << input_data.front() << " - INCORRECT!" << '\n';
				input_data.pop_front();
			}
		}
		
	}
	
	output.close();
}

bool Algorithm::IsCorrect(std::shared_ptr<HierarchicalList> h_list)
{
	bool is_correct = false;
	bool is_div = false;
	std::shared_ptr<Node> temp1 = h_list->Back();
	if (h_list->IsAtom(temp1) && (std::get<char>(temp1->value) == '+' || std::get<char>(temp1->value) == '-' 
								|| std::get<char>(temp1->value) == '*' || std::get<char>(temp1->value) == '/')) 
	{
		if (std::get<char>(temp1->value) == '/') {
			is_div = true;
		}
		is_correct = true;
	}

	std::shared_ptr<Node> temp = h_list->Front();

	for (int i = 0; i < h_list->Length(); i++) {
		if (!is_correct) {
			break;
		}

		if (h_list->IsAtom(temp)) {

			char temp_char = std::get<char>(temp->value);

			if ((temp_char >= 'a' && temp_char <= 'z') || (temp_char >= '0' && temp_char <= '9'))
			{
				if (temp_char == '0' && is_div) {
					is_correct = false;
				}
				temp = temp->next;
			}
			else if (temp_char == '+' || temp_char == '-' || temp_char == '*' || temp_char == '/') {
				if (temp->next != nullptr ) 
				{
					is_correct = false;
				}
				else {
					is_correct = true;
				}
			}
			else {
				is_correct = false;
			}
		}
		else {
			is_correct = this->IsCorrect(std::get<std::shared_ptr<HierarchicalList>>(temp->value));
			temp = temp->next;
		}
	}
	return is_correct;
}

std::list<std::string> Algorithm::InputData()
{
	std::ifstream input("./Tests/input.txt");
	std::list<std::string> list;
	std::string str;

	if (input.is_open()) {
		
		while (std::getline(input, str)) {
			list.push_back(str);
		}
	}
	else {
		std::cout << "Can't open input file!" << std::endl;
	}

	input.close();
	
	return list;
}


