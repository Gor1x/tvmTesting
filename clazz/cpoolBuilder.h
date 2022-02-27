#pragma once

#include <iostream>
#include <memory>

namespace CPool {
    class Builder {
    private:
        Data _data{};
        size_t _index;
        u2 _size;
    
    public:
        Builder(u2 size) {
            _index = 1;
            _size = size;
        }

        Builder& utf8(u2 size, std::shared_ptr<u1> data) {
            // TODO: add entries to _data._utf8Entries or to _data._utf8EntriesWide

            _data._types.insert(std::pair(_index, Tag_Utf8));
            _index++;

            return *this;
        }

        Builder& const_long(int64_t value) {
            _data._types.insert(std::pair(_index, Tag_Long));
            _data._longEntries.insert(std::pair(_index, value));
            _index+=2;

            return *this;
        }


        Builder& const_double(u8 value) {
            _data._types.insert(std::pair(_index, Tag_Double));
            _data._doubleEntries.insert(std::pair(_index, value));
            _index += 2;

            return *this;
        }

        Builder& const_integer(s4 value) {
            _data._types.insert(std::pair(_index, Tag_Integer));
            _data._integerEntries.insert(std::pair(_index, value));
            _index++;

            return *this;
        }

        Builder& const_float(u4 value) {
            _data._types.insert(std::pair(_index, Tag_Float));
            _data._floatEntries.insert(std::pair(_index, value));
            _index++;

            return *this;
        }

        Builder& const_class(u2 nameIndex) {
            _data._types.insert(std::pair(_index, Tag_Class));
            _data._classEntries.insert(std::pair(_index, nameIndex));
            _index++;

            return *this;
        }

        Builder& const_string(u2 stringIndex) {
            _data._types.insert(std::pair(_index, Tag_String));
            _data._stringEntries.insert(std::pair(_index, stringIndex));
            _index++;

            return *this;
        }

        Builder& fieldRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_FieldRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder& methodRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_MethodRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder& interfaceMethodRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_InterfaceMethodRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder& nameAndType(NameTypeRecord nameTypeData) {
            _data._types.insert(std::pair(_index, Tag_NameAndType));
            _data._nameAndTypeEntries.insert(std::pair(_index, nameTypeData));
            _index++;

            return *this;
        }

        Builder& methodHandle(HandleRecord handleData) {
            _data._types.insert(std::pair(_index, Tag_MethodHandle));
            _data._handleEntries.insert(std::pair(_index, handleData));
            _index++;

            return *this;
        }

        Builder& methodType(u2 descriptorIndex) {
            _data._types.insert(std::pair(_index, Tag_MethodType));
            _data._methodTypeEntries.insert(std::pair(_index, descriptorIndex));
            _index++;

            return *this;
        }

        Builder& dynamic(DynamicRecord dynamicData) {
            _data._types.insert(std::pair(_index, Tag_Dynamic));
            _data._dynamicEntries.insert(std::pair(_index, dynamicData));
            _index++;

            return *this;
        }

        Builder& invokeDynamic(DynamicRecord dynamicData) {
            _data._types.insert(std::pair(_index, Tag_InvokeDynamic));
            _data._dynamicEntries.insert(std::pair(_index, dynamicData));
            _index++;

            return *this;
        }

        Builder& module(u2 nameIndex) {
            _index++;
            return *this;
        }

        Builder& package(u2 nameIndex) {
            _index++;
            return *this;
        }


        std::shared_ptr<CPool::Entity> build() {
            auto value = new CPool::Entity(_data, _size);
            return std::shared_ptr<CPool::Entity>(value);
        }
    };
};

