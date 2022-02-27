
add_library(classprinter classprinter.cc typeUtil.cc)

target_compile_features(classprinter PRIVATE cxx_std_20)

target_include_directories(classprinter PUBLIC
                          "${PROJECT_SOURCE_DIR}"
                          )


