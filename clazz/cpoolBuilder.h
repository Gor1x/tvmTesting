#pragma once

#include <iostream>
#include <memory>

namespace CPool {
    class Builder {
    private:
        Data _data{};
        size_t _index;
        u2 _size;

        template<typename T>
        std::pair<bool, T> readString(u2 size, std::shared_ptr<u1> data) {
            T res;
            bool isAscii = true;
            auto bytes = data.get();
            for (int i = 0; i < size;) {
                if ((bytes[i] & 0b1000000) == 0) {
                    res += char(bytes[i] & 0b01111111);
                    i++;
                } else if ((bytes[i] & 0b11100000) == 0b11000000) {
                    res += char(((bytes[i] & 0x1f) << 6) + (bytes[i + 1] & 0x3f));
                    i += 2;
                } else if ((bytes[i] & 0b11110000) == 0b11100000) {
                    res += char(((bytes[i] & 0xf) << 12) + ((bytes[i + 1] & 0x3f) << 6) + (bytes[i + 2] & 0x3f));
                    i += 3;
                    isAscii = false;
                } else {
                    res += char(0x10000 + ((bytes[i + 1] & 0x0f) << 16) + ((bytes[i + 2] & 0x3f) << 10) +
                                ((bytes[i + 4] & 0x0f) << 6) + (bytes[i + 5] & 0x3f));
                    isAscii = false;
                    i += 6;
                }
            }
            return {isAscii, res};
        }

    public:
        Builder(u2 size) {
            _index = 1;
            _size = size;
        }

        Builder &utf8(u2 size, std::shared_ptr<u1> data) {
            auto pair = readString<std::u16string>(size, data);
            bool isAscii = pair.first;
            if (isAscii)
                _data._utf8Entries[_index] = readString<std::string>(size, data).second;
            else
                _data._utf8EntriesWide[_index] = pair.second;

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


        Builder &const_double(u8 value) {
            _data._types.insert(std::pair(_index, Tag_Double));
            _data._doubleEntries.insert(std::pair(_index, value));
            _index += 2;

            return *this;
        }

        Builder &const_integer(s4 value) {
            _data._types.insert(std::pair(_index, Tag_Integer));
            _data._integerEntries.insert(std::pair(_index, value));
            _index++;

            return *this;
        }

        Builder &const_float(u4 value) {
            _data._types.insert(std::pair(_index, Tag_Float));
            _data._floatEntries.insert(std::pair(_index, value));
            _index++;

            return *this;
        }

        Builder &const_class(u2 nameIndex) {
            _data._types.insert(std::pair(_index, Tag_Class));
            _data._classEntries.insert(std::pair(_index, nameIndex));
            _index++;

            return *this;
        }

        Builder &const_string(u2 stringIndex) {
            _data._types.insert(std::pair(_index, Tag_String));
            _data._stringEntries.insert(std::pair(_index, stringIndex));
            _index++;

            return *this;
        }

        Builder &fieldRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_FieldRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder &methodRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_MethodRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder &interfaceMethodRef(RefRecord referenceData) {
            _data._types.insert(std::pair(_index, Tag_InterfaceMethodRef));
            _data._refEntries.insert(std::pair(_index, referenceData));
            _index++;

            return *this;
        }

        Builder &nameAndType(NameTypeRecord nameTypeData) {
            _data._types.insert(std::pair(_index, Tag_NameAndType));
            _data._nameAndTypeEntries.insert(std::pair(_index, nameTypeData));
            _index++;

            return *this;
        }

        Builder &methodHandle(HandleRecord handleData) {
            _data._types.insert(std::pair(_index, Tag_MethodHandle));
            _data._handleEntries.insert(std::pair(_index, handleData));
            _index++;

            return *this;
        }

        Builder &methodType(u2 descriptorIndex) {
            _data._types.insert(std::pair(_index, Tag_MethodType));
            _data._methodTypeEntries.insert(std::pair(_index, descriptorIndex));
            _index++;

            return *this;
        }

        Builder &dynamic(DynamicRecord dynamicData) {
            _data._types.insert(std::pair(_index, Tag_Dynamic));
            _data._dynamicEntries.insert(std::pair(_index, dynamicData));
            _index++;

            return *this;
        }

        Builder &invokeDynamic(DynamicRecord dynamicData) {
            _data._types.insert(std::pair(_index, Tag_InvokeDynamic));
            _data._dynamicEntries.insert(std::pair(_index, dynamicData));
            _index++;

            return *this;
        }

        Builder &module(u2 nameIndex) {
            _index++;
            return *this;
        }

        Builder &package(u2 nameIndex) {
            _index++;
            return *this;
        }


        std::shared_ptr<CPool::Entity> build() {
            auto value = new CPool::Entity(_data, _size);
            return std::shared_ptr<CPool::Entity>(value);
        }
    };
};

