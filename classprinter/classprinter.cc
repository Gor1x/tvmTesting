#include "classprinter.h"


#include <map>
#include <memory>
#include <iostream>
#include <bitset>
#include <iomanip>

std::string tagRepr(size_t tag) {
    std::array<std::string, 21> repr = {
        "?",                  // 0
        "Utf8",               // 1
        "?",                  // 2
        "Integer",            // 3
        "Float",              // 4
        "Long",               // 5
        "Double",             // 6
        "Class",              // 7
        "String",             // 8
        "FieldRef",           // 9
        "MethodRef",          // 10
        "InterfaceMethodRef", // 11
        "NameAndType",        // 12
        "?",                  // 13
        "?",                  // 14
        "MethodHandle",       // 15
        "MethodType",         // 16
        "Dynamic",            // 17
        "InvokeDynamic",      // 18
        "Module",             // 19
        "Package",            // 20
     };

    return repr[tag];
}


void ClassPrinter::printAll() {
    printVersion();
    std::cout << std::endl;
    printCPool(); 
    std::cout << std::endl;
    printClassFlags();
    std::cout << std::endl;
    printThisClass();
    std::cout << std::endl;
    printSuperClass();
    std::cout << std::endl;
    printInterfaces();
    std::cout << std::endl;
    printFields();
    std::cout << std::endl;
    printMethods();
    std::cout << std::endl;
    printAttributes();
}

void ClassPrinter::printVersion() {
    ClassVersion version = _clazz->version();
    std::cout << "Version " << version.major() << "." << version.minor() << std::endl;
}

void ClassPrinter::printCPool() {
        auto cpool = _clazz->cpool();
        std::cout << "Constant Pool size " << cpool->size() << std::endl;

        for (size_t i = 1; i < cpool->size(); ++i) {
           auto tag = cpool->typeTag(i);
           std::cout << i << ": ";
           std::cout << "Tag " << tag;
           std::cout << " " << tagRepr(tag) << " ";

           switch (tag) {
               case CPool::Tag_Integer: {
                   auto value = cpool->integerValue(i);
                   std::cout << "Value " << value << ", hex: 0x" << std::hex << value;
                   std::cout << std::dec;
               }
               break;

               case CPool::Tag_Float: {
                   auto value = cpool->floatBits(i);
                   std::cout << "Bits " << std::bitset<32>(value);
                   std::cout << std::setw(8) << std::setfill('0');
                   std::cout << ", hex: 0x" << std::hex << value;
                   std::cout << std::dec;
               }
               break;

               case CPool::Tag_Long: {
                   std::cout << "Value " << cpool->longValue(i);
                   std::cout << std::dec;
                   ++i;
               }
               break;

               case CPool::Tag_Double: {
                   auto value = cpool->doubleBits(i);
                   std::cout << "Bits " << std::bitset<64>(value);
                   std::cout << std::setw(16) << std::setfill('0');
                   std::cout << ", hex: 0x" << std::hex << value;
                   std::cout << std::dec;

                   ++i;
               }
               break;

               case CPool::Tag_Utf8: {
                   if (cpool->utf8IsWide(i)) { 
                       std::cout << "Value Wide \"";
                       std::cout << std::hex;
                       for (auto c16: cpool->wideString(i)) {
                           std::cout << "\\" << (int)c16;
                       }
                       std::cout << std::dec;
                   } else {
                       std::cout << "Value \"";
                       std::cout << cpool->ascii(i);
                   }
                   std::cout << "\"";
               }
               break;

               case CPool::Tag_String: {
                   std::cout << "Contents " << cpool->stringContents(i);
               }
               break;

               case CPool::Tag_Class: {
                   std::cout << "Name index " << cpool->classNameIndex(i);
               }
               break;

               case CPool::Tag_FieldRef: {
                   std::cout << "Class index " << cpool->refClassIndex(i) << ", ";
                   std::cout << "Name and type index " << cpool->refNameTypeIndex(i);
               }
               break;

               case CPool::Tag_MethodRef: {
                   std::cout << "Class index " << cpool->refClassIndex(i) << ", ";
                   std::cout << "Name and type index " << cpool->refNameTypeIndex(i);
               }
               break;

               case CPool::Tag_InterfaceMethodRef: {
                   std::cout << "Class index " << cpool->refClassIndex(i) << ", ";
                   std::cout << "Name and type index " << cpool->refNameTypeIndex(i);
               }
               break;

               case CPool::Tag_NameAndType: {
                   std::cout << "Name index " << cpool->nameIndex(i) << ", ";
                   std::cout << "Description index " << cpool->descriptionIndex(i);
               }
               break;

               case CPool::Tag_InvokeDynamic: {
                   std::cout << "Bootstrap index " << cpool->bootstrapIndex(i) << ", ";
                   std::cout << "NameAndType index " << cpool->dynamicNameTypeIndex(i);
               }
               break;

               case CPool::Tag_MethodHandle: {
                   std::cout << "Kind " << (int)cpool->referenceKind(i) << ", ";
                   std::cout << "Index " << cpool->referenceIndex(i);
               }
               break;

               case CPool::Tag_MethodType: {
                   std::cout << "Descriptor index " << (int)cpool->methodTypeDescriptorIndex(i);
               }
               break;
           }
           std::cout << std::endl; 
        }
    }

void ClassPrinter::printClassFlags() {
    printFlags(_clazz->flags().value(), _clazz->flags().asStrings());
}

void ClassPrinter::printFieldFlags(Field _field) {
    printFlags(_field.flags().value(), _field.flags().asStrings());
}

void ClassPrinter::printMethodFlags(Method _method) {
    printFlags(_method.flags().value(), _method.flags().asStrings());
}

void ClassPrinter::printFlags(u2 value, std::vector<std::string> stringRepr) {
    std::cout << "Flags: " << "decimal " << value;
    std::cout << ", hex " << std::setw(4) << std::setfill('0') << std::hex << value;
    std::cout << ", binary " << std::bitset<16>(value);

    for (auto e: stringRepr) {
        std::cout << " " << e;
    }
    std::cout << std::endl;
    std::cout << std::dec;
    }


void ClassPrinter::printThisClass() {
    auto thisClass = _clazz->thisClass();
    std::cout << "This class: " << "id " << _clazz->thisClassId();
    std::cout << ", name " << thisClass->externalName();
    std::cout << std::endl;
}

void ClassPrinter::printSuperClass() {
    auto superClass = _clazz->superClass();
    std::cout << "Super class: " << "id " << _clazz->superClassId();
    std::cout << ", name " << superClass->externalName();
    std::cout << std::endl;
}

void ClassPrinter::printInterfaces() {
    auto interfaces = _clazz->interfaces();
    auto interfaceIds = _clazz->interfaceIds();

    if (interfaces.empty()) {
        std::cout << "No interfaces" << std::endl;
        return;
    }

    std::cout << "Implements class ids";
    for (auto id: interfaceIds) {
        std::cout << " " << id;
    }
    std::cout << std::endl;

    std::cout << "Implements names";
    for (auto item: interfaces) {
        std::cout << " " << item->externalName();
    }
    std::cout << std::endl;
}

void ClassPrinter::printFields() {
        auto fields = _clazz->fields();

        if (fields.empty()) {
            std::cout << "No fields" << std::endl;
            return;
        }

        for (u2 index = 0; index < fields.size(); ++index) {
            auto field = fields[index];
            auto fieldData = _clazz->fieldData(index);
            std::cout << "Field ";
            std::cout << "name " << field->name() << " (index " << fieldData.nameIndex  << ")";
            std::cout << ", type " << field->type() << " (descriptor index " << fieldData.descriptorIndex  << ")";
            std::cout << std::endl;

            std::cout << "Human type: " << TypeUtil::field_external(field->type()).type << std::endl;

            printFieldFlags(*field);

            if (field->attributes().empty()) {
                std::cout << "No field attributes" << std::endl;
                continue;
            }
            for (auto attribute: field->attributes()) {
                std::cout << "Field attribute name " << attribute.name() << ", size " << attribute.size() << std::endl;
            }
        }

    }

void ClassPrinter::printMethods() {
    auto methods = _clazz->methods();

    if (methods.empty()) {
        std::cout << "No methods" << std::endl;
        return;
    }

    for (u2 index = 0; index < methods.size(); ++index) {
        auto method = methods[index];
        auto methodData = _clazz->methodData(index);
        std::cout << "Method ";
        std::cout << "name " << method->name() << " (index " << methodData.nameIndex  << ")";
        std::cout << ", type " << method->type() << " (descriptor index " << methodData.descriptorIndex  << ")";
        std::cout << std::endl;

        auto humanType = TypeUtil::method_external(method->type());
        std::cout << "Human type: (";
        for (size_t pi = 0; pi < humanType.parameterTypes.size(); ++pi) {
            if (pi > 0) {
                std::cout << ", ";
            }
            std::cout << humanType.parameterTypes[pi];
        }
        std::cout << "): " << humanType.resultType << std::endl;

        printMethodFlags(*method);

        if (method->attributes().empty()) {
            std::cout << "No method attributes" << std::endl;
            continue;
        }
        for (auto attribute: method->attributes()) {
            std::cout << "Method attribute name " << attribute.name() << ", size " << attribute.size() << std::endl;
        }
    }
}

void ClassPrinter::printAttributes() {
    auto attributes = _clazz->attributes();

    if (attributes.empty()) {
        std::cout << "No class attributes" << std::endl;
        return;
    }

    for (auto attribute: attributes) {
        std::cout << "Class attribute name " << attribute.name() << ", size " << attribute.size() << std::endl;
    }
}

