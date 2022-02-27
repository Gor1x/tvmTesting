#pragma once

#include "fieldFlags.h"
#include "attributeData.h"

#include <vector>

struct FieldData {
    FieldFlags flags;
    u2 nameIndex;
    u2 descriptorIndex;
    std::vector<AttributeData> attributes;
};

