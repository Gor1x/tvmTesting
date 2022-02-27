#pragma once

#include <memory>

struct AttributeData {
    u2 nameIndex;
    u4 size;
    std::shared_ptr<u1> body;
};

