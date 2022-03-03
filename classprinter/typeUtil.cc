#include "typeUtil.h"
#include <iostream>

std::vector<std::string> readFieldTypes(std::string descriptor) {
    std::vector<std::string> result;

    auto descriptorIterator = descriptor.begin();
    while (descriptorIterator != descriptor.end()) {

        std::string arrayPart;
        while (descriptorIterator != descriptor.end() && *descriptorIterator == '[')
            arrayPart += "[]";

        std::string currentType;

        if (*descriptorIterator == 'L') {
            descriptorIterator++;
            while (*descriptorIterator != ';') {
                currentType += *descriptorIterator;
                descriptorIterator++;
            }
        }
        if (*descriptorIterator == 'B')
            currentType = "byte";
        if (*descriptorIterator == 'C')
            currentType = "char";
        if (*descriptorIterator == 'D')
            currentType = "double";
        if (*descriptorIterator == 'F')
            currentType = "float";
        if (*descriptorIterator == 'I')
            currentType = "int";
        if (*descriptorIterator == 'J')
            currentType = "long";
        if (*descriptorIterator == 'S')
            currentType = "short";
        if (*descriptorIterator == 'Z')
            currentType = "boolean";
        if (*descriptorIterator == 'V')
            currentType = "void";
        descriptorIterator++;
        result.push_back(currentType + arrayPart);
    }
    return result;
}

FieldSignature TypeUtil::field_external(std::string descriptor) {
    return {readFieldTypes(descriptor)[0]};
}

MethodSignature TypeUtil::method_external(std::string descriptor) {
    int splitPos = descriptor.find(')');
    if (splitPos == -1) {
        return {{""}, ""};
    }
    std::string params = descriptor.substr(1, splitPos - 1);
    std::string returnType = descriptor.substr(splitPos + 1);

    /**         MethodSignature's fields should be:
        * vector of parameter types, where each position corresponds with each method parameter
          and is the same that would be returned by field_external some corresponding description
        * return type in human form (the same as it would be for field_external)
    */

    return {readFieldTypes(params), readFieldTypes(returnType)[0]};
}

