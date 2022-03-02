#pragma once

#include <memory>

#include "methodData.h"
#include "method.h"
#include "attributeData.h"
#include "cpool.h"

class MethodBuilder {
private:
    MethodData _data;

public:
    MethodBuilder() {
    }

    MethodBuilder &flags(u2 value) {
        _data.flags = MethodFlags{value};
        return *this;
    }

    MethodBuilder &nameIndex(u2 value) {
        _data.nameIndex = value;
        return *this;
    }

    MethodBuilder &descriptorIndex(u2 value) {
        _data.descriptorIndex = value;
        return *this;
    }

    MethodBuilder &attribute(u2 nameIndex, u4 size, std::shared_ptr<u1> data) {
        _data.attributes.push_back(AttributeData{nameIndex, size, data});
        return *this;
    }

    MethodBuilder &attribute(AttributeData data) {
        _data.attributes.push_back(data);
        return *this;
    }

    std::shared_ptr<Method> build(std::shared_ptr<CPool::Entity> cpool) {
        /**
         * pretty much the same as for Field. Look at field builder for details
         */
        auto name = cpool->ascii(_data.nameIndex);
        auto descr = cpool->ascii(_data.descriptorIndex);
        auto flags = _data.flags;

        std::vector<Attribute> attributes;
        for (const auto& g : _data.attributes) {
            attributes.emplace_back(cpool->ascii(g.nameIndex), g.size, g.body);
        }

        return std::make_shared<Method>(name, descr, flags, attributes);
    }

    MethodData data() {
        return _data;
    }
};

