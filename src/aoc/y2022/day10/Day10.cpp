#include "Day10.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 10);

    int registerX = 1;
    int cycle = 1;

    int out = 0;
    std::vector<std::string> imageOut{};

    for(const std::string& operation: input) {
        std::vector<std::string> splitOperation{};
        strings::split(splitOperation, operation, " ");
        
        if(operation == "noop") {
            imageOut.push_back((registerX - 1 <= (cycle-1) % 40 && (cycle-1) % 40 <= registerX + 1)? "#": ".");
            cycle++;    // end of cycle

            if((cycle - 20) % 40 == 0) {
                std::cout << "register X has value " << registerX << " at cycle " << cycle << std::endl;
                out += registerX * cycle;
            }
        }

        else if(splitOperation[0] == "addx") {
            imageOut.push_back((registerX - 1 <= (cycle-1) % 40 && (cycle-1) % 40 <= registerX + 1)? "#": ".");
            cycle++;    // end of cycle

            if((cycle - 20) % 40 == 0) {
                std::cout << "register X has value " << registerX << " at cycle " << cycle << std::endl;
                out += registerX * cycle;
            }

            imageOut.push_back((registerX - 1 <= (cycle-1) % 40 && (cycle-1) % 40 <= registerX + 1)? "#": ".");
            cycle++;    // end of cycle
            
            registerX += std::stoi(splitOperation[1]);
            if((cycle - 20) % 40 == 0) {
                std::cout << "register X has value " << registerX << " at cycle " << cycle << std::endl;
                out += registerX * cycle;
            }
        }
    }
    print() << out;
    print();

    for(int i = 0; i < imageOut.size(); i++) {
        if(i % 40 == 0) std::cout << std::endl;
        std::cout << imageOut.at(i);
    }

    return 0;
}