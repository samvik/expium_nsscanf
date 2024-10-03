
file(GLOB SRC_FILES *.c)

add_library(nsscanf ${SRC_FILES})
target_compile_features(nsscanf PRIVATE c_std_11)
target_link_libraries(nsscanf PRIVATE m)
target_include_directories(nsscanf PUBLIC ./)
