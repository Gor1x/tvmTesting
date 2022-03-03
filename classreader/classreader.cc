#include "classreader.h"
#include "clazz/classBuilder.h"
#include "clazz/fieldFlags.h"
#include "clazz/fieldBuilder.h"
#include "clazz/methodBuilder.h"
#include "clazz/attributeData.h"

#include <vector>

std::shared_ptr<Clazz> ClassReader::readClass() {
    ClassBuilder builder;

    _fd = open(_fileName.c_str(), O_RDONLY);

    if (_fd < 0) {
        _isFailed = true;
        return nullptr;
    }

    u4 v = read<u4>();
    if (_isFailed) {
        _isFailed = true;
        close(_fd);
        return nullptr;
    }

    u2 minor = read<u2>();
    u2 major = read<u2>();

    builder.version({major, minor});
    builder.cpool(readCPool());
    builder.flags(read<u2>());
    builder.thisClass(read<u2>());
    builder.superClass(read<u2>());

    u2 interfacesCount = read<u2>();
    std::vector<u2> data(interfacesCount);
    for (int i = 0; i < interfacesCount; i++) {
        data[i] = read<u2>();
    }
    builder.interfaces(data);

    u2 fieldsCount = read<u2>();
    for (int i = 0; i < fieldsCount; i++) {
        FieldBuilder fieldBuilder;
        fieldBuilder
                .flags(read<u2>())
                .nameIndex(read<u2>())
                .descriptorIndex(read<u2>());
        u2 attr_count = read<u2>();
        for (int j = 0; j < attr_count; j++) {
            fieldBuilder.attribute(readAttributeData());
        }
        builder.field(fieldBuilder);
    }

    u2 methodCount = read<u2>();
    for (int i = 0; i < methodCount; i++) {
        MethodBuilder methodBuilder;
        methodBuilder
                .flags(read<u2>())
                .nameIndex(read<u2>())
                .descriptorIndex(read<u2>());
        u2 attr_count = read<u2>();
        for (int j = 0; j < attr_count; j++) {
            methodBuilder.attribute(readAttributeData());
        }
        builder.method(methodBuilder);
    }

    u2 attributesCount = read<u2>();
    for (int j = 0; j < attributesCount; j++) {
        builder.attribute(readAttributeData());
    }
    /*
     *  For interfaces method you must pass vector of constant
     *  pool indices
     *
     *  For methods and fields
     *     1. Create MethodBuilder/Field builder for each method/field
     *     2. Call flags/nameIndex/descriptorIndex of method/field builder as
     *        appropriate
     *     3. For each attribute call builder's attribute method
     *     4. When you are done with specific field/method, call class builder's
     *        method named "field" or "method"
     *     Don't call explicitly here build method of builder of field/method.
     *
     *   For each class attribute call 'attribute' method of class builder
     *
     */


    return builder.build();
}

std::shared_ptr<CPool::Entity> ClassReader::readCPool() {
    u2 cpCount = read<u2>() - 1;
    CPool::Builder cpBuilder{cpCount};
    for (int i = 0; i < cpCount; i++) {
        u1 tag = read<u1>();
        switch (tag) {
            case CPool::Tag_Integer: {
                cpBuilder.const_integer(read<u4>());
            }
                break;

            case CPool::Tag_Float: {
                cpBuilder.const_float(read<u4>());
            }
                break;

            case CPool::Tag_Long: {
                auto high = read<u4>();
                auto low = read<u4>();
                cpBuilder.const_long(((long long) high << 32) + low);
            }
                break;

            case CPool::Tag_Double: {
                auto high = read<u4>();
                auto low = read<u4>();
                cpBuilder.const_double(((long long) high << 32) + low);
            }
                break;

            case CPool::Tag_Utf8: {
                u2 size = read<u2>();
                auto data = std::shared_ptr<u1>(new u1[size]);
                fill(data, size);
                cpBuilder.utf8(size, data);
            }
                break;

            case CPool::Tag_String: {
                cpBuilder.const_string(read<u2>());
            }
                break;

            case CPool::Tag_Class: {
                cpBuilder.const_class(read<u2>());
            }
                break;

            case CPool::Tag_FieldRef: {
                cpBuilder.fieldRef(CPool::RefRecord{read<u2>(), read<u2>()});
            }
                break;

            case CPool::Tag_MethodRef: {
                cpBuilder.methodRef(CPool::RefRecord{read<u2>(), read<u2>()});
            }
                break;

            case CPool::Tag_InterfaceMethodRef: {
                cpBuilder.interfaceMethodRef(CPool::RefRecord{read<u2>(), read<u2>()});
            }
                break;

            case CPool::Tag_NameAndType: {
                cpBuilder.nameAndType(CPool::NameTypeRecord{read<u2>(), read<u2>()});
            }
                break;

            case CPool::Tag_InvokeDynamic: {
                cpBuilder.invokeDynamic(CPool::DynamicRecord{read<u2>(), read<u2>()});
            }
                break;

            case CPool::Tag_MethodHandle: {
                cpBuilder.methodHandle(CPool::HandleRecord{read<u1>(), read<u2>()});
            }
                break;

            case CPool::Tag_MethodType: {
                cpBuilder.methodType(read<u2>());
            }
                break;

            case CPool::Tag_Module: {
                cpBuilder.module(read<u2>());
            }
                break;

            case CPool::Tag_Package: {
                cpBuilder.package(read<u2>());
            }
                break;
        }
    }
    /*
     * use 'read' or 'fill' methods to get file contents
     *
     * Mapping between constant pool tag and
     * builder method is following:
     *
     * Utf8 - utf8(length, data) where data is shared_ptr to bytes array
     * Long - const_long
     * Double - long_double
     * Integer - const_integer
     * Float - const_float
     * Class - const_class
     * String - const_string
     * FieldRef - fieldRef
     * MethodRef - methodRef
     * InterfaceMethodRef - interfaceMethodRef
     * NameAndType - nameAndType
     * MethodHandle - methodHandle
     * MethodType - methodType
     * Dynamic - invokeDynamic
     * InvokeDynamic - invokeDynamic
     * Module - module
     * Package - package
     */

    return cpBuilder.build();
}

AttributeData ClassReader::readAttributeData() {
    u2 name = read<u2>();
    u4 length = read<u4>();
    std::shared_ptr<u1> info(new u1(length));
    fill(info, length);
    return AttributeData{name, length, info};
}

