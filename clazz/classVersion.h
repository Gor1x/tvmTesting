#pragma once

#include "types.h"

#include <cstdint>
#include <utility>

/**
 * Immutable class representing class version
 * as part of Clazz file
 *
 */
class ClassVersion {
    u2 _major;
    u2 _minor;

public:
    ClassVersion(u2 major, u2 minor): _major{major}, _minor{minor} {
    }

    ClassVersion(): _major{0}, _minor{0} {
    }

    u2 major() const {
        return _major;
    }

    u2 minor() const {
        return _minor;
    }
};

