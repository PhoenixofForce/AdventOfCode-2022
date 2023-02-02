#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <functional>

#define defaultDebug [](const State& s){ return ""; }
#define defaultPrune [](const State& best, const State& current){ return false; }

template<typename T>
using StateGenerator = std::function<void(std::vector<T>&, const T&)>; //void(*)(std::vector<T>&, const T&);

template<typename T>
using StateConfirmer =  std::function<bool(const T&)>; //bool(*)(const T&);

template<typename T>
using Hasher =  std::function<size_t(const T&)>;

template<typename T>
using Debug =  std::function<std::string(const T&)>; //bool(*)(const T&);

template<typename T>
using Pruner =  std::function<bool(const T&, const T&)>;

namespace paths {

/** Finds the shortest path
  * @param start the first State from which you want to find an end state
  * @param generator a function which generates states that can be reached from a given state
  * @param confirmer a function  that returns true, when a given state is a desired goal
  * @param doOuput should optional debug outputs be made? (default: true)
  * @param returnFirst should the search return the first found (aka shortest) path? if false it returns the last found (aka longest) path (default: true)
  * @return the found end state
  */
template <typename State>
State a_star(const State& start, StateGenerator<State> generator, StateConfirmer<State> confirmer, Hasher<State> hasher, 
        bool doOutput = true, bool returnFirst = true, 
        Debug<State> debugger = defaultDebug, Pruner<State> shouldPrune = defaultPrune) {
            
    auto equal = [](const State& a, const State& b){ return a == b; };
    auto comp = [](const State& a, const State& b){ return (a < b); };//maybe make this redefinable as well 

    std::priority_queue<State, std::vector<State>, decltype(comp)> queue(comp);
    std::unordered_set<State, decltype(hasher), decltype(equal)> visited(10, hasher, equal);
    queue.push(start);

    State best{start};

    int iterations{};   
    State last{ start };
    while (!queue.empty()) {
        State current{ queue.top() };
        queue.pop();

        if(visited.find(current) != visited.end()) continue;
        visited.insert(current);

        if(iterations%1000 == 0) {
            if(doOutput) std::cout << iterations << " searched; " << queue.size() << " in queue; " << debugger(current) << std::endl;
        }
        iterations++;

        if(confirmer(current)) {
            if(returnFirst) {
                std::cout << "searched a total of " << iterations << " states" << std::endl;
                return current;
            }
            last = current;
            continue;
        }

        if(shouldPrune(best, current)) {
            continue;
        }

        std::vector<State> newStates{};
        generator(newStates, current);
        for(State s: newStates) {
            if(visited.find(s) == visited.end()) {
                queue.push(s);
                if(!comp(s, best)) best = s;
            }
        }
    }
    std::cout << "searched a total of " << iterations << " states" << std::endl;
    
    return last;
}

};

#endif