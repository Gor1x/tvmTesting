#pragma once

#include <string>

#include "attribute.h"

class Field {
private:
    std::string _name;
    std::string _type;
    FieldFlags _flags; 
    std::vector<Attribute> _attributes;

public:
    Field(std::string name, std::string type, FieldFlags flags, std::vector<Attribute> attributes):
        _name{name}, _type{type}, _flags{flags}, _attributes{attributes} {
    }

    std::string name() {
        return _name;
    }

    std::string type() {
        return _type;
    }

    FieldFlags flags() {
        return _flags;
    }

    std::vector<Attribute> attributes() {
        return _attributes;
    }
};

