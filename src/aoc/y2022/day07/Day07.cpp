#include "Day07.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 07);

    file root{ "/" };
    file* current{ &root };

    //index filesystem
    for(int lineIndex = 1; lineIndex < input.size(); lineIndex++) {
        std::string& line = input.at(lineIndex);

        if(line.find("$") == std::string::npos) {
            if(line.find("dir") == 0) {
                std::vector<std::string> splitLine{};
                strings::split(splitLine, line, " ");

                std::string dirName{ splitLine.at(1) };
                current->addDir(dirName);
            } else {
                std::vector<std::string> splitLine{};
                strings::split(splitLine, line, " ");

                int size = std::stoi(splitLine.at(0));
                std::string dirName{ splitLine.at(1) };
                current->addFile(dirName, size);
            }
        }

        else {
            std::vector<std::string> splitLine{};
            strings::split(splitLine, line, " ");

            if(splitLine.at(1) == "cd") {
                if(splitLine.at(2) == "..") current = current->parent;
                else current = current->findDir(splitLine.at(2));
            }

        }
    }

    //vars for part 1
    int threshHold = 100000; 
    std::vector<int> filesSmallerThanThreshhold{};
    std::vector<file> open{};
    open.push_back(root);

    //vars for part 2
    int totalSpace = 70000000;
    int neededSpaceForUpdate = 30000000;
    int freeSpace = totalSpace - root.getSize();
    int spaceToDelete = neededSpaceForUpdate - freeSpace;
    std::vector<file> filesThatCouldBeDeleted{};

    //scan filesystem
    while(open.size() > 0) {
        file current = open.at(0);
        open.erase(open.begin());

        if(current.isDir()) {
            if(current.getSize() <= threshHold) filesSmallerThanThreshhold.push_back(current.getSize());    //part 1
            if(current.getSize() > spaceToDelete) filesThatCouldBeDeleted.push_back(current);               //part 2
        }

        for(const file& f: current.subfiles) {
            open.push_back(f);   
        }
    }

    //print solution
    print() << Stream<int>::of(filesSmallerThanThreshhold).sum(0);
    print() << Stream<file>::of(filesThatCouldBeDeleted)
        .sort([](const file& a, const file& b){ return a.getSize() < b.getSize(); })
        .findFirst()
        .value()
        .getSize();

    return 0;
}