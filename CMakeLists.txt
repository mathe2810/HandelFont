cmake_minimum_required(VERSION 3.23)
project(HandelFont C)

set(CMAKE_C_STANDARD 17)

add_executable(HandelFont main.c)

target_link_libraries(HandelFont -lalleg44 -lmingw32)
