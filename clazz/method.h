#pragma once

#include <string>

#include "attribute.h"

class Method {
private:
    std::string _name;
    std::string _type;
    MethodFlags _flags; 
    std::vector<Attribute> _attributes;

public:
    Method(std::string name, std::string type, MethodFlags flags, std::vector<Attribute> attributes):
        _name{name}, _type{type}, _flags{flags}, _attributes{attributes} {
    }

    std::string name() {
        return _name;
    }

    std::string type() {
        return _type;
    }

    MethodFlags flags() {
        return _flags;
    }

    std::vector<Attribute> attributes() {
        return _attributes;
    }
};

