#pragma once

#include "classVersion.h"
#include "classFlags.h"
#include "cpool.h"
#include "classData.h"

#include <map>
#include <memory>

class ClassBuilder {
private:
    const std::shared_ptr<ClassData> _data;

public:
    ClassBuilder() : _data{std::shared_ptr<ClassData>{new ClassData()}} {
    }

    ClassBuilder *version(ClassVersion value) {
        _data->version = value;
        return this;
    }

    ClassBuilder *cpool(std::shared_ptr<CPool::Entity> cpool) {
        _data->cpool = cpool;
        return this;
    }

    ClassBuilder *flags(u2 value) {
        _data->flags = ClassFlags{value};
        return this;
    }

    ClassBuilder *thisClass(u2 value) {
        _data->thisClass = value;
        return this;
    }

    ClassBuilder *superClass(u2 value) {
        _data->superClass = value;
        return this;
    }

    ClassBuilder *interfaces(std::vector<u2> value) {
        _data->interfaces = value;
        return this;
    }

    ClassBuilder *field(FieldBuilder value) {
        _data->fields.push_back(value);
        return this;
    }

    ClassBuilder *method(MethodBuilder value) {
        _data->methods.push_back(value);
        return this;
    }

    ClassBuilder *attribute(u2 nameIndex, u4 size, std::shared_ptr<u1> data) {
        _data->attributes.push_back(AttributeData{nameIndex, size, data});
        return this;
    }

    ClassBuilder *attribute(const AttributeData &data) {
        _data->attributes.push_back(data);
        return this;
    }

    std::shared_ptr<Clazz> build() {
        return std::make_shared<Clazz>(_data);
    }

};

