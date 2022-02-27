#pragma once

#include <string>

class Attribute {
private:
    std::string _name;
    u4 _size;
    std::shared_ptr<u1> _body;

public:
    Attribute(std::string name, u4 size, std::shared_ptr<u1> body): _name{name}, _size{size}, _body{body} {
    }

    std::string name() {
        return _name;
    }

    u4 size() {
        return _size;
    }
};

