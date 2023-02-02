#ifndef STREAM_H
#define STREAM_H

#include <functional>
#include <optional>
#include <algorithm>

template<typename T>
class Stream {

public:

static Stream<T> of(std::vector<T> list) {
    return Stream{ list };
}

//>--| PUSH

Stream& push(const T& t) {
    list.push_back(t);
    return *this;
}

Stream& push(const std::vector<T>& vec) {
    for(const T& t: vec) {
        list.push_back(t);
    }

    return *this;
}

Stream& push(const Stream<T>& s) {
    for(const T& t: s.list) {
        list.push_back(t);
    }

    return *this;
}

//>--| FILTERING

Stream& filter(std::function<bool(int, const T&)> filterFunction) {
    std::vector<bool> toDelete{};
    for(int i = 0; i < list.size(); i++) {
        toDelete.push_back(!filterFunction(i, list.at(i)));
    }

    for(int i = toDelete.size() - 1; i >= 0; i--) {
        if(toDelete.at(i)) list.erase(list.begin() + i);
    }

    return *this;
}

Stream& filter(std::function<bool(const T&)> filterFunction) {
    std::function<bool(const T&)> realFilter{ [filterFunction](const T& t){ return !filterFunction(t); } };

    list.erase(std::remove_if(list.begin(), list.end(), realFilter), list.end());
    return *this;
}

Stream& limit(int length) {
    return filter([length](int i, const T& b){ return i < length; });
}

Stream<T>& skip(int n) {
    return filter([n](int i, const T& t){ return i >= n; });
}

Stream<T> distinct() {
    std::vector<T> out{};

    for(const T& t: list) {
        if(out.size() == 0 || std::find(out.begin(), out.end(), t) == out.end()) {
            out.push_back(t);
        }
    }

    list = out;
    return *this;
}

//>--| ELEMENT MANIPULATION

Stream& forEach(std::function<void(const T&)> forEachFunction) {
    for(int i = 0; i < list.size(); i++) {
        forEachFunction(list.at(i));
    }

    return *this;
}

template<class U>
Stream<U> map(std::function<U(const T&)> mapFunction) {
    std::vector<U> out{};
    for(int i = 0; i < list.size(); i++) {
        out.push_back(mapFunction(list.at(i)));
    }
    return Stream<U>::of(out);
}

template<class U>
Stream<U> flatten(std::function<std::vector<U>(const T&)> flatFunction) {
    std::vector<U> out{};
    for(int i = 0; i < list.size(); i++) {
        for(U u: flatFunction(list.at(i))) {
            out.push_back(u);
        }
    }
    return Stream<U>::of(out);
}

Stream<std::vector<T>> group(int size) {
    std::vector<std::vector<T>> out{};
    
    for(int i = 0; i < list.size(); i += size) {
        std::vector<T> batch{};
        for(int j = 0; j < size; j++) {
            if(i + j < list.size()) batch.push_back(list.at(i + j));
        }
        
        out.push_back(batch);
    }   

    return Stream<std::vector<T>>::of(out);
}

Stream<std::vector<T>> group(std::function<bool(const T& first, const T& current)> areElementsSameBatch) {
    std::vector<std::vector<T>> out{};
    
    std::vector<T> batch{};
    if(list.size() > 0) batch.push_back(list.at(0));

    for(int i = 1; i < list.size(); i++) {
        if(areElementsSameBatch(batch.at(0), list.at(i))) {
            batch.push_back(list.at(i));
        } else {
            out.push_back(batch);
            batch = {};
            batch.push_back(list.at(i));
        }
    } 
    out.push_back(batch);

    return Stream<std::vector<T>>::of(out);
}

//>--| ORDER MANIPULATION

Stream& sort(std::function<bool(const T& a, const T& b)> comp = [](const T& a, const T& b){ return a < b; }) {
    std::sort(list.begin(), list.end(), comp);
    return *this;
}

Stream& reverse() {
    std::reverse(list.begin(), list.end());
    return *this;
}

//>--| STREAM PROPERTIES(allMatch, anyMatch, noneMatch)

int countMatch(std::function<bool(int, const T&)> boolFunction) {
    int out = 0;
    for(int i = 0; i < list.size(); i++) {
        if(boolFunction(i, list.at(i))) out++;
    }

    return out;
}

bool allMatch(std::function<bool(int, const T&)> boolFunction) {
    for(int i = 0; i < list.size(); i++) {
        if(!boolFunction(i, list.at(i))) return false;
    }

    return true;
}

bool anyMatch(std::function<bool(int, const T&)> boolFunction) {
    for(int i = 0; i < list.size(); i++) {
        if(boolFunction(i, list.at(i))) return true;
    }

    return false;
}

bool notAllMatch(std::function<bool(int, const T&)> boolFunction) {
    bool foundTrue = false;
    bool foundFalse = false;
    for(int i = 0; i < list.size(); i++) {
        if(!boolFunction(i, list.at(i))) foundFalse = true;
        if(boolFunction(i, list.at(i))) foundTrue = true;

        if(foundFalse && foundTrue) return true;
    }

    return false;
}

bool noneMatch(std::function<bool(int, const T&)> boolFunction) {
    for(int i = 0; i < list.size(); i++) {
        if(boolFunction(i, list.at(i))) return false;
    }

    return true;
}

//>--| STREAM PROPERTIES(findFirst, min, max, sum, reduce)

std::optional<T> findFirst() {
    if(list.size() > 0) return list.at(0);
    return {};
}


std::optional<T> min() {
    return sort().findFirst();
}

std::optional<T> max() {
    return sort(std::greater<T>()).findFirst();
}

template<class U>
U sum(U identity) {
    U result{ identity };
    for(const T& t: list) {
        result += t;
    }

    return result;
}

template<class U>
U reduce(U identity, std::function<U(U& res, const T& e)> reducer) {
    U result{ identity };
    for(const T& t: list) {
        result = reducer(result, t);
    }

    return result;
}

int size() {
    return list.size();
}

//>--| EXPORT

std::vector<T> toVector() {
    return list;
}

template<class K, class V>
std::map<K, V> toMap(std::function<K(const T&)> key, std::function<V(const T&)> value) {
    std::map<K, V> out{};

    for(const T& t: list) {
        map[key(t)] = value(t);
    }

    return out;
}

Stream& print() {
    std::cout << "[";
    for(int i = 0; i < list.size(); i++) {
        std::cout << list.at(i);
        if(i != list.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    return *this;
}

private:
    Stream(std::vector<T> list): list(list) {}
    std::vector<T> list;
};

#endif