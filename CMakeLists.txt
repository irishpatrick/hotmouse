cmake_minimum_required(VERSION 3.0)

project(hotmouse)

set(CFLAGS ${CFLAGS} /W3)
file(GLOB sources *.c)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})