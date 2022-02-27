
add_library(classreader classreader.cc)

target_compile_features(classreader PRIVATE cxx_std_20)

target_include_directories(classreader PUBLIC
                          "${PROJECT_SOURCE_DIR}"
                          )


