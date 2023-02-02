#ifndef SETS_H
#define SETS_H

#include "stream.h"

#include <vector>
#include <algorithm>

namespace sets {

    template<class T>
    void unionSets(std::vector<T>& out, const std::vector<T>& in1, const std::vector<T>& in2) {
        out.clear();
        for(T t: in1) out.push_back(t);
        for(T t: in2) out.push_back(t);
    }

    template<class T>
    void unionSets(std::vector<T>& inOut, const std::vector<T>& in2) {
        std::vector<T> out{};
        unionSets(out, inOut, in2);
        inOut = out;
    }


    template<class T>
    void intersectSets(std::vector<T>& out, const std::vector<T>& in1, const std::vector<T>& in2, bool careDouble = false) {
        out.clear();
        std::vector<T> in2Copy{ in2 };

        for(T t: in1) {
            auto positionInCopy{ std::find(in2Copy.begin(), in2Copy.end(), t) }; 
            if(positionInCopy != in2Copy.end()) {
                if(careDouble) in2Copy.erase(positionInCopy);
                out.push_back(t);
            }
        }

        if(!careDouble) out = Stream<T>::of(out).distinct().toVector();
    }

    template<class T>
    void intersectSets(std::vector<T>& inOut, const std::vector<T>& in2, bool careDouble = false) {
        std::vector<T> out{};
        intersectSets(out, inOut, in2, careDouble);
        inOut = out;
    }

    template<class T>
    void withoutSets(std::vector<T>& out, const std::vector<T>& in1, const std::vector<T>& in2, bool careDouble = false) {
        out.clear();
        for(T t: in1) out.push_back(t);
        std::vector<T> in2Copy{ in2 };

        for(T t: in1) {
            auto positionInCopy{ std::find(in2Copy.begin(), in2Copy.end(), t) }; 
            if(positionInCopy != in2Copy.end()) {
                if(careDouble) in2Copy.erase(positionInCopy);
                out.erase(t);
            }
        }
    }

    template<class T>
    void withoutSets(std::vector<T>& inOut, const std::vector<T>& in2, bool careDouble = false) {
        std::vector<T> out{};
        withoutSets(out, inOut, in2, careDouble);
        inOut = out;
    }
}


#endif