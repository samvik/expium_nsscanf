
file(GLOB SRC_FILES catch2/*.cpp *.cpp)

add_executable(nsscanf-test ${SRC_FILES})
target_compile_features(nsscanf-test PRIVATE cxx_std_20)
target_link_libraries(nsscanf-test PRIVATE nsscanf)
