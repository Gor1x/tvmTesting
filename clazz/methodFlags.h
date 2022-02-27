#pragma once

#include "types.h"

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

class MethodFlags {
private:
    const static u2 ACC_PUBLIC = 0x0001;
    const static u2 ACC_PRIVATE = 0x0002;
    const static u2 ACC_PROTECTED = 0x0004;
    const static u2 ACC_STATIC = 0x0008;
    const static u2 ACC_FINAL = 0x0010;
    const static u2 ACC_SYNCHRONIZED = 0x0020;
    const static u2 ACC_BRIDGE = 0x0040;
    const static u2 ACC_VARARGS = 0x0080;
    const static u2 ACC_NATIVE = 0x0100;
    const static u2 ACC_ABSTRACT = 0x0400;
    const static u2 ACC_STRICT = 0x0800;
    const static u2 ACC_SYNTHETIC = 0x1000;
 
    u2 _value;

public:
    MethodFlags(u2 value): _value(value) {
    }

    MethodFlags(): _value(0) {
    }

    MethodFlags(MethodFlags& right): _value(right._value) {
    }

    MethodFlags(const MethodFlags& right): _value(right._value) {
    }

    u2 value() const {
        return _value;
    }

    bool is_public() const {
        return (ACC_PUBLIC & _value) != 0;
    }

    bool is_private() const {
        return (ACC_PRIVATE & _value) != 0;
    }

    bool is_protected() const {
        return (ACC_PROTECTED & _value) != 0;
    }

    bool is_static() const {
        return (ACC_STATIC & _value) != 0;
    }

    bool is_final() const {
        return (ACC_FINAL & _value) != 0;
    }

    bool is_synchronized() const {
        return (ACC_SYNCHRONIZED & _value) != 0;
    }

    bool is_bridge() const {
        return (ACC_BRIDGE & _value) != 0;
    }

    bool is_varargs() const {
        return (ACC_VARARGS & _value) != 0;
    }

    bool is_native() const {
        return (ACC_NATIVE & _value) != 0;
    }

    bool is_abstract() const {
        return (ACC_ABSTRACT & _value) != 0;
    }

    bool is_strict() const {
        return (ACC_STRICT & _value) != 0;
    }

    bool is_synthetic() const {
        return (ACC_SYNTHETIC & _value) != 0;
    }

    const std::vector<std::string> asStrings() const {
        std::vector<std::string> result;

        if (is_public()) {
            result.push_back("public");
        }

        if (is_private()) {
            result.push_back("private");
        }

        if (is_protected()) {
            result.push_back("protected");
        }

        if (is_static()) {
            result.push_back("static");
        }

        if (is_final()) {
            result.push_back("final");
        }

        if (is_synchronized()) {
            result.push_back("synchronized");
        }

        if (is_bridge()) {
            result.push_back("bridge");
        }

        if (is_varargs()) {
            result.push_back("varargs");
        }

        if (is_native()) {
            result.push_back("native");
        }

        if (is_abstract()) {
            result.push_back("abstract");
        }

        if (is_strict()) {
            result.push_back("strict");
        }

        if (is_synthetic()) {
            result.push_back("synthetic");
        }

        return result;
    }
};

