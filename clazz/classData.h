#pragma once

#include "classVersion.h"
#include "classFlags.h"
#include "cpool.h"
#include "fieldBuilder.h"
#include "methodBuilder.h"

#include <vector>

struct ClassData {
    ClassVersion version;
    std::shared_ptr<CPool::Entity> cpool;
    ClassFlags flags;
    u2 thisClass;
    u2 superClass;
    std::vector<u2> interfaces;
    std::vector<FieldBuilder> fields;
    std::vector<MethodBuilder> methods;
    std::vector<AttributeData> attributes;

    std::shared_ptr<ClassInfo> classInfo(u2 classId) {
        return std::shared_ptr<ClassInfo>(new ClassInfo{cpool->className(classId)});
    }
};

