#ifndef COMBINATIONS_H
#define COMBINATOINS_H

#include <string>
#include <vector>

template<typename T>
void rotations(std::vector<std::vector<T>>& combinationsOut, std::vector<T> input) {
    for(int i = 0; i < input.size(); i++) {
        combinationsOut.push_back(input);
        
        T element{ input.at(0) };
        input.erase(input.begin());
        input.push_back(element);
    }
}

template<typename T>
void combinations(std::vector<std::vector<T>>& combinationsOut, std::vector<T> input, int length, int startPos, std::vector<T>& current) {
    if(length == 0) {
        combinationsOut.push_back(current);
        return;
    }

    for(int i = startPos; i <= input.size() - length; i++) {
        current.push_back(input.at(i));
        combinations(combinationsOut, input, length - 1, i + 1, current);
        current.pop_back();
    }
}

template<typename T>
void combinations(std::vector<std::vector<T>>& combinationsOut, std::vector<T> input, int length) {
    std::vector<T> current{};
    combinations(combinationsOut, input, length, 0, current);
}


#endif