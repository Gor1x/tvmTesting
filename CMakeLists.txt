
cmake_minimum_required(VERSION 3.10)

# set the project name

project(tvm)

add_subdirectory(clazz)
add_subdirectory(classreader)
add_subdirectory(classprinter)
add_executable(tvm tvm.cc)

target_link_libraries(tvm PUBLIC clazz classreader classprinter)

target_compile_features(tvm PRIVATE cxx_std_20)


target_include_directories(tvm PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/clazz"
                          "${PROJECT_SOURCE_DIR}/classreader"
                          "${PROJECT_SOURCE_DIR}/classprinter"
                          )

