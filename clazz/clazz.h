#pragma once

#include "classVersion.h"
#include "classFlags.h"
#include "classInfo.h"
#include "cpoolData.h"
#include "cpool.h"
#include "cpoolBuilder.h"
#include "classData.h"
#include "field.h"

#include <map>
#include <memory>

class Clazz {
private:
    std::shared_ptr<ClassData> _data;
    std::shared_ptr<ClassInfo> _thisClass;
    std::shared_ptr<ClassInfo> _superClass;
    std::vector<std::shared_ptr<ClassInfo>> _interfaces;
    std::vector<std::shared_ptr<Field>> _fields;
    std::vector<FieldData> _fieldsData;
    std::vector<std::shared_ptr<Method>> _methods;
    std::vector<MethodData> _methodsData;
    std::vector<Attribute> _attributes;


public:
    Clazz(std::shared_ptr<ClassData> data): _data{data} {
        _thisClass = _data->classInfo(_data->thisClass);
        _superClass = _data->classInfo(_data->superClass);

        for (auto interfaceId: _data->interfaces) {
            _interfaces.push_back(_data->classInfo(interfaceId));
        }

        for (auto fieldBuilder: _data->fields) {
            _fields.push_back(fieldBuilder.build(_data->cpool));
        }

        for (auto f: _data->fields) {
            _fieldsData.push_back(f.data());
        }

        for (auto methodBuilder: _data->methods) {
            _methods.push_back(methodBuilder.build(_data->cpool));
        }

        for (auto m: _data->methods) {
            _methodsData.push_back(m.data());
        }

        auto cpool = _data->cpool;
        for (auto attrData: _data->attributes) {
            _attributes.push_back(Attribute{cpool->ascii(attrData.nameIndex), attrData.size, attrData.body});
        }
    }

    ClassVersion version() {
        return _data->version;
    }

    std::shared_ptr<CPool::Entity> cpool() {
        return _data->cpool;
    }

    ClassFlags flags() {
        return _data->flags;
    }

    std::shared_ptr<ClassInfo> thisClass() {
        return _thisClass;
    }

    std::shared_ptr<ClassInfo> superClass() {
        return _superClass;
    }

    std::vector<std::shared_ptr<ClassInfo>> interfaces() {
        return _interfaces;
    }

    std::vector<std::shared_ptr<Field>> fields() {
        return _fields;
    }

    std::vector<std::shared_ptr<Method>> methods() {
        return _methods;
    }

    u2 thisClassId() {
        return _data->thisClass;
    }

    u2 superClassId() {
        return _data->superClass;
    }

    std::vector<u2> interfaceIds() {
        return _data->interfaces;
    }

    FieldData fieldData(u2 index) {
        return _fieldsData[index];
    }

    MethodData methodData(u2 index) {
        return _methodsData[index];
    }

    std::vector<Attribute> attributes() {
        return _attributes;
    }
};

