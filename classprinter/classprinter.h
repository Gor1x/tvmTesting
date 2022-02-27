#pragma once

#include "clazz/classVersion.h"
#include "clazz/classFlags.h"
#include "clazz/classInfo.h"
#include "clazz/cpoolData.h"
#include "clazz/cpool.h"
#include "clazz/clazz.h"
#include "clazz/cpoolBuilder.h"
#include "clazz/classData.h"
#include "typeUtil.h"

#include <map>
#include <memory>
#include <iostream>
#include <bitset>
#include <iomanip>

class ClassPrinter {
private:
    std::shared_ptr<Clazz> _clazz;

public:
    ClassPrinter(std::shared_ptr<Clazz> clazz): _clazz{clazz} {
    }

    void printAll();

    void printVersion();

    void printCPool();

    void printClassFlags();

    void printFieldFlags(Field _field);

    void printMethodFlags(Method _method);

    void printFlags(u2 value, std::vector<std::string> stringRepr);

    void printThisClass();

    void printSuperClass();

    void printInterfaces();

    void printFields();

    void printMethods();

    void printAttributes();
};

