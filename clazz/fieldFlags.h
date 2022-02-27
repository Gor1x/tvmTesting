#pragma once

#include "types.h"

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

class FieldFlags {
private:
    const static u2 ACC_PUBLIC = 0x0001;
    const static u2 ACC_PRIVATE = 0x0002;
    const static u2 ACC_PROTECTED = 0x0004;
    const static u2 ACC_STATIC = 0x0008;
    const static u2 ACC_FINAL = 0x0010;
    const static u2 ACC_VOLATILE = 0x0040;
    const static u2 ACC_TRANSIENT = 0x0080;
    const static u2 ACC_SYNTHETIC = 0x1000;
    const static u2 ACC_ENUM = 0x4000;
 
    u2 _value;

public:
    FieldFlags(u2 value): _value(value) {
    }

    FieldFlags(): _value(0) {
    }

    FieldFlags(FieldFlags& right): _value(right._value) {
    }

    FieldFlags(const FieldFlags& right): _value(right._value) {
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

    bool is_volatile() const {
        return (ACC_VOLATILE & _value) != 0;
    }

    bool is_transient() const {
        return (ACC_TRANSIENT & _value) != 0;
    }

    bool is_synthetic() const {
        return (ACC_SYNTHETIC & _value) != 0;
    }

    bool is_enum() const {
        return (ACC_ENUM & _value) != 0;
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

        if (is_volatile()) {
            result.push_back("volatile");
        }

        if (is_transient()) {
            result.push_back("transient");
        }

        if (is_synthetic()) {
            result.push_back("synthetic");
        }

        if (is_enum()) {
            result.push_back("enum");
        }

        return result;
    }
};

