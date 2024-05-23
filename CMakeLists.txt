
cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_COMPILER /usr/bin/clang)
project(Dnealar LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")
add_compile_options("-O3")
add_compile_options("-fvisibility=hidden")

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options("-Wno-nullability-extension")
endif()

#add_link_options("-s")

file(GLOB SOURCES CONFIGURE_DEPENDS include/dnealar/*.h src/*.c src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} GL GLEW m ${PROJECT_SOURCE_DIR}/libs/cglm/bin/libcglm.so)
target_include_directories(${PROJECT_NAME} PRIVATE include ${PROJECT_SOURCE_DIR}/libs/cglm/include)

set(DEMO demo)
add_subdirectory(${DEMO})

file(COPY ${DEMO}/res DESTINATION ${CMAKE_BINARY_DIR}/demo)
