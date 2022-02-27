#pragma once

#include <string>

class MethodInfo {
private:
    std::string _name;

public:
    MethodInfo(std::string name): _name{name} {
    }

    std::string name() {
        return _name;
    }
};

