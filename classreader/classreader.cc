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
   
    /*
     * TODO: implement reading other
     *   elements of class file and call relevant builder
     *   method
     *
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
    uint16_t cpCount = read<uint16_t>();
    CPool::Builder cpBuilder{cpCount};

    /*
     * TODO:
     *  call one of CPool::Builder's method for each constant pool entry
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

