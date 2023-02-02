#ifndef DAY07_H
#define DAY07_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct file{
    std::string name{};
    int size{};
    std::vector<file> subfiles{};
    file* parent{ nullptr };

    int getSize() const {
        if(size > 0) {
            return size; 
        }

        int out = 0;
        for(const file& f: subfiles) out += f.getSize();
        return out;
    }

    file* getParent() {
        return parent;
    }

    bool hasParent() {
        return parent;
    }

    bool isDir() {
        return size == 0;
    }

    void addDir(const std::string& name) {
        file newDir{ name, 0, {}, this};
        subfiles.push_back(newDir);
    }

    file* findDir(const std::string& wantedName) {
        auto wantedPos = std::find_if(subfiles.begin(), subfiles.end(), [wantedName](const file& f){ return f.name == wantedName; });
        if(wantedPos == subfiles.end()) return nullptr;
        return &(*wantedPos);
    }

    void addFile(const std::string& name, int size) {
        file newDir{ name, size, {}, this};
        subfiles.push_back(newDir);
    }
};

#endif