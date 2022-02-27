#include "typeUtil.h"
#include <iostream>

FieldSignature TypeUtil::field_external(std::string descriptor) {
   /** TODO:
       implement conversion of type descriptor
       to human type.

       FieldSignature should be:
       * "int", "boolean", "char" etc. if descriptor is JVM descriptor of corresponding
         primitive type
       * convential type name if descriptor is JVM descriptor of one of reference types
         (for example, it must return "java.lang.String" if it is descriptor of
          such class)
       * <typename>[] if descriptor is JVM descriptor of array type and return value
         for type of array element would be <typename>
   */

   return {""};
}

MethodSignature TypeUtil::method_external(std::string descriptor) {
   /** TODO:
       implement conversion of type descriptor
       to human type.

       MethodSignature's fields should be:
       * vector of parameter types, where each position corresponds with each method parameter
         and is the same that would be returned by field_external some corresponding description
       * return type in human form (the same as it would be for field_external)
   */

    return {{}, ""};
}

