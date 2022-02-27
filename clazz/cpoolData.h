#pragma once

#include "types.h"
#include <map>

namespace CPool {
    struct RefRecord {
        u2 classIndex;
        u2 nameAndTypeIndex;
    };

    struct NameTypeRecord {
        u2 nameIndex;
        u2 typeIndex;
    };

    struct DynamicRecord {
        u2 bootstrapIndex;
        u2 nameAndTypeIndex;
    };

    struct HandleRecord {
        u1 referenceKind;
        u2 referenceIndex;
    };

    struct Data {
        std::map<u2, std::string> _utf8Entries;
        std::map<u2, std::u16string> _utf8EntriesWide;
        std::map<u2, s8> _longEntries;
        std::map<u2, u8> _doubleEntries;
        std::map<u2, s4> _integerEntries;
        std::map<u2, u4> _floatEntries;
        std::map<u2, u2> _classEntries;
        std::map<u2, u2> _stringEntries;
        std::map<u2, RefRecord> _refEntries;
        std::map<u2, NameTypeRecord> _nameAndTypeEntries;
        std::map<u2, DynamicRecord> _dynamicEntries;
        std::map<u2, HandleRecord> _handleEntries;
        std::map<u2, u2> _methodTypeEntries;

        std::map<u2, int> _types;
    };
}

