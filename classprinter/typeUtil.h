#pragma once

#include <string>
#include <vector>

struct FieldSignature {
    std::string type;
};

struct MethodSignature {
    std::vector<std::string> parameterTypes;
    std::string resultType;
};

class TypeUtil {
public:
    static FieldSignature field_external(std::string descriptor);
    static MethodSignature method_external(std::string descriptor);
};
 
