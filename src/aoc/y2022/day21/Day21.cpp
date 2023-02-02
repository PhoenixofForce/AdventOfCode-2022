#include "Day21.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 21);

    std::map<std::string, TreePiece> operationTree{};
    buildOperationTree(input, operationTree);
    
    TreePiece root{ operationTree["root"] };
    print() << root.getValue(operationTree) << std::endl;

    bool leftHasHumn = root.leftContains(operationTree, "humn");
    long long notHumnSide = leftHasHumn? operationTree[root.right].getValue(operationTree): operationTree[root.left].getValue(operationTree);

    TreePiece current{ leftHasHumn? operationTree[root.left]: operationTree[root.right] };
    long long currentShouldEqual = notHumnSide;
    while(current.name != "humn" && !current.isLeaf()) {
        leftHasHumn = current.leftContains(operationTree, "humn");

        currentShouldEqual = leftHasHumn? current.reverseUnknownLeft(operationTree, currentShouldEqual):
            current.reverseUnknownRight(operationTree, currentShouldEqual);

        current = leftHasHumn? operationTree[current.left]: operationTree[current.right];
    }
    print() << current.name << " == " << currentShouldEqual;

    return 0;
}

void buildOperationTree(std::vector<std::string> input, std::map<std::string, TreePiece>& values) {
    for(int i = 0; i < input.size(); i++) {
        std::vector<std::string> splitLine{};
        strings::split(splitLine, input.at(i), " ");
        
        if(splitLine.size() == 2) {
            std::string name{ splitLine.at(0).substr(0, 4) };
            std::string val = splitLine.at(1);
            values[name] = TreePiece{ name, val, "#", ""};
        }

        else {
            std::string name{ splitLine.at(0).substr(0, 4) };
            std::string left{ splitLine.at(1) };
            std::string op{ splitLine.at(2) };
            std::string right{ splitLine.at(3) };

            values[name] = TreePiece{name, left, op, right};
        }
    }
}