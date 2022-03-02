#pragma once

#include "types.h"
#include "cpoolData.h"

namespace CPool {
    enum {
        Tag_Utf8 = 1,
        Tag_Integer = 3,
        Tag_Float = 4,
        Tag_Long = 5,
        Tag_Double = 6,
        Tag_Class = 7,
        Tag_String = 8,
        Tag_FieldRef = 9,
        Tag_MethodRef = 10,
        Tag_InterfaceMethodRef = 11,
        Tag_NameAndType = 12,
        Tag_MethodHandle = 15,
        Tag_MethodType = 16,
        Tag_Dynamic = 17,
        Tag_InvokeDynamic = 18,
        Tag_Module = 19,
        Tag_Package = 20,
    };

    std::string tagRepr(size_t tag);

    class Entity {
    private:
        CPool::Data _data;
        u2 _size;

    public:
        Entity(CPool::Data data, u2 size) : _data{data}, _size{size} {
        }

        u2 size() {
            return _size;
        }

        u2 typeTag(u2 index) {
            return _data._types.at(index);
        }

        s4 integerValue(u2 index) {
            return _data._integerEntries.find(index)->second;
        }

        s8 longValue(u2 index) {
            return _data._longEntries.find(index)->second;
        }

        u4 floatBits(u2 index) {
            return _data._floatEntries.find(index)->second;
        }

        u8 doubleBits(u2 index) {
            return _data._doubleEntries.find(index)->second;
        }

        u2 stringContents(u2 index) {
            return _data._stringEntries.find(index)->second;
        }

        std::string ascii(u2 index) {
            return _data._utf8Entries.find(index)->second;
        }

        bool utf8IsWide(u2 index) {
            return _data._utf8EntriesWide.find(index) != _data._utf8EntriesWide.end();
        }

        std::u16string wideString(u2 index) {
            return _data._utf8EntriesWide.find(index)->second;
        }

        u2 classNameIndex(u2 index) {
            return _data._classEntries.find(index)->second;
        }

        u2 refClassIndex(u2 index) {
            return _data._refEntries.find(index)->second.classIndex;
        }

        u2 refNameTypeIndex(u2 index) {
            return _data._refEntries.find(index)->second.nameAndTypeIndex;
        }

        u2 nameIndex(u2 index) {
            return _data._nameAndTypeEntries.find(index)->second.nameIndex;
        }

        u2 descriptionIndex(u2 index) {
            return _data._nameAndTypeEntries.find(index)->second.typeIndex;
        }

        u2 bootstrapIndex(u2 index) {
            return _data._dynamicEntries.find(index)->second.bootstrapIndex;
        }

        u2 dynamicNameTypeIndex(u2 index) {
            return _data._dynamicEntries.find(index)->second.nameAndTypeIndex;
        }

        u2 referenceKind(size_t index) {
            return _data._handleEntries.find(index)->second.referenceKind;
        }

        u2 referenceIndex(size_t index) {
            return _data._handleEntries.find(index)->second.referenceIndex;
        }

        u2 methodTypeDescriptorIndex(size_t index) {
            return _data._methodTypeEntries.find(index)->second;
        }

        std::string className(size_t index) {
            /*
             * TODO: implement method to report string representation of class
               name by constant pool entry index

               It should use some of above defined methods as helpers
             */
            return ascii(index);
        }

    };
};

