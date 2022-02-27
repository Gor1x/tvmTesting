#pragma once

#include "types.h"

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

class ClassFlags {
private:
    const static u2 ACC_PUBLIC = 0x0001;
    const static u2 ACC_FINAL = 0x0010;
    const static u2 ACC_SUPER = 0x0020;
    const static u2 ACC_INTERFACE = 0x0200;
    const static u2 ACC_ABSTRACT = 0x0400;
    const static u2 ACC_SYNTHETIC = 0x1000;
    const static u2 ACC_ANNOTATION = 0x2000;
    const static u2 ACC_ENUM = 0x4000;
    const static u2 ACC_MODULE = 0x8000;
 
    u2 _value;

public:
    ClassFlags(u2 value): _value(value) {
    }

    ClassFlags(): _value(0) {
    }

    ClassFlags(ClassFlags& right): _value(right._value) {
    }

    ClassFlags(const ClassFlags& right): _value(right._value) {
    }

    u2 value() const {
        return _value;
    }

    bool is_public() const {
        return (ACC_PUBLIC & _value) != 0;
    }

    bool is_final() const {
        return (ACC_FINAL & _value) != 0;
    }

    bool is_super() const {
        return (ACC_SUPER & _value) != 0;
    }

    bool is_interface() const {
        return (ACC_INTERFACE & _value) != 0;
    }

    bool is_abstract() const {
        return (ACC_ABSTRACT & _value) != 0;
    }

    bool is_synthetic() const {
        return (ACC_SYNTHETIC & _value) != 0;
    }

    bool is_annotation() const {
        return (ACC_ANNOTATION & _value) != 0;
    }

    bool is_enum() const {
        return (ACC_ENUM & _value) != 0;
    }

    bool is_module() const {
        return (ACC_MODULE & _value) != 0;
    }

    const std::vector<std::string> asStrings() const {
        std::vector<std::string> result;

        if (is_public()) {
            result.push_back("public");
        }

        if (is_final()) {
            result.push_back("final");
        }

        if (is_super()) {
            result.push_back("super");
        }

        if (is_interface()) {
            result.push_back("interface");
        }

        if (is_abstract()) {
            result.push_back("abstract");
        }

        if (is_synthetic()) {
            result.push_back("synthetic");
        }

        if (is_annotation()) {
            result.push_back("annotation");
        }

        if (is_enum()) {
            result.push_back("enum");
        }

        if (is_module()) {
            result.push_back("module");
        }

        return result;
    }
};

