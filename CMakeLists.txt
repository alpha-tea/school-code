cmake_minimum_required(VERSION 3.5)

project(school-code LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(school-code main.c chapter_01.c chapter_02.c)
