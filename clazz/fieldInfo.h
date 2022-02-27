#pragma once

#include <string>

class FieldInfo {
private:
    std::string _name;

public:
    FieldInfo(std::string name): _name{name} {
    }

    std::string name() {
        return _name;
    }

};

