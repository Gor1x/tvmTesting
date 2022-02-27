#pragma once

#include "methodFlags.h"
#include "attributeData.h"

#include <vector>

struct MethodData {
    MethodFlags flags;
    u2 nameIndex;
    u2 descriptorIndex;
    std::vector<AttributeData> attributes;
};

