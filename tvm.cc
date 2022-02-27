#include <iostream>
#include <string>

#include "classreader/classreader.h"
#include "classprinter/classprinter.h"


int main(int argc, char* argv[]) {
    if (argc == 1) return 0;

    ClassReader classReader{argv[1]};

    auto clazz = classReader.readClass();

    if (argc > 2 && (std::string{argv[2]} == "-printClass")) {
        auto printer = new ClassPrinter(clazz);

        printer->printAll();
    }
}

