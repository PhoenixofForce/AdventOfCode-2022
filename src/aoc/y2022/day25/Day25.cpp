#include "Day25.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 25);

    long long out = 0;
    for(std::string& line: input) {
        long long current = 0;
        
        for(int i = 0; i < line.size(); i++) {
            long long value = (line.size() - i + -1);
            value = std::pow(5, value);
            
            char c = line.at(i);
            long long quantity =  (c == '1'? 1: 
                            (c == '2'? 2: 
                            (c == '0'? 0: 
                            (c == '-'? -1: 
                            (c == '='? -2: 0)))));

            current += value * quantity;
        }

        out += current;
        std::cout << "   " << line << "   =>    " << current << std::endl;
    }

    std::string snafuOut{ "" };
    while(out != 0) {
        int remainder = out % 5;

        if(remainder == 0 || remainder == 1 || remainder == 2) snafuOut = std::to_string(remainder) + snafuOut; 
        if(remainder == 3) {
            snafuOut = "=" + snafuOut;
            out += 5;
        }
        if(remainder == 4) {
            snafuOut = "-" + snafuOut;
            out += 5;
        }


        out /= 5;
    }

    print() << snafuOut << std::endl;;

    return 0;
}