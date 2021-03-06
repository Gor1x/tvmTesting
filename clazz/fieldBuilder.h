#pragma once

#include <memory>

#include "fieldData.h"
#include "field.h"
#include "attributeData.h"

class FieldBuilder {
private:
    FieldData _data;

public:
    FieldBuilder() {
    }

    FieldBuilder &flags(u2 value) {
        _data.flags = FieldFlags{value};
        return *this;
    }

    FieldBuilder &nameIndex(u2 value) {
        _data.nameIndex = value;
        return *this;
    }

    FieldBuilder &descriptorIndex(u2 value) {
        _data.descriptorIndex = value;
        return *this;
    }

    FieldBuilder &attribute(u2 nameIndex, u4 size, std::shared_ptr<u1> data) {
        _data.attributes.push_back(AttributeData{nameIndex, size, data});
        return *this;
    }

    FieldBuilder &attribute(AttributeData data) {
        _data.attributes.push_back(data);
        return *this;
    }

    std::shared_ptr<Field> build(std::shared_ptr<CPool::Entity> cpool) {
        /**
         * You need to prepare name, type descriptor, flags and attributes
         * For name and descriptor you need to obtain string representation
         * based on there ids and constant pool data
         *
         * You also need to resolve name of each attribute
         */
        auto name = cpool->ascii(_data.nameIndex);
        auto descr = cpool->ascii(_data.descriptorIndex);
        auto flags = _data.flags;

        std::vector<Attribute> attributes;
        for (const auto& g : _data.attributes) {
            attributes.emplace_back(cpool->ascii(g.nameIndex), g.size, g.body);
        }

        return std::make_shared<Field>(name, descr, flags, attributes);
    }

    FieldData data() {
        return _data;
    }
};

