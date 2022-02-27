#pragma once

#include "methodData.h"
#include "method.h"
#include "attributeData.h"

class MethodBuilder {
private:
    MethodData _data;

public:
    MethodBuilder() {
    }

    MethodBuilder& flags(u2 value) {
        _data.flags = MethodFlags{value};
        return *this;
    }

    MethodBuilder& nameIndex(u2 value) {
        _data.nameIndex = value;
        return *this;
    }

    MethodBuilder& descriptorIndex(u2 value) {
        _data.descriptorIndex = value;
        return *this;
    }

    MethodBuilder& attribute(u2 nameIndex, u4 size, std::shared_ptr<u1> data) {
        _data.attributes.push_back(AttributeData{nameIndex, size, data});
        return *this;
    }

    std::shared_ptr<Method> build(std::shared_ptr<CPool::Entity> cpool) {
        /**
         * TODO: create Method instance here and return shared pointer to its instance
         *
         * pretty much the same as for Field. Look at field builder for details
         */

        return std::shared_ptr<Method>(new Method{name, descr, flags, attributes});
    }

    MethodData data() {
        return _data;
    }
};

