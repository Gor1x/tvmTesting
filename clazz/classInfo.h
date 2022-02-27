#pragma once

#include <string>

class ClassInfo {
private:
    std::string _name;
    std::string _externalName;

public:
    ClassInfo(std::string name): _name{name} {
        _externalName = _name;
        for (size_t i=0; i < _externalName.size(); ++i) {
            if (_externalName[i] == '/') {
                _externalName[i] = '.';
            }
        }
    }

    std::string name() {
        return _name;
    }

    std::string externalName() {
        return _externalName;
    }
};

