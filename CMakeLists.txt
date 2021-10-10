cmake_minimum_required(VERSION 3.5)

project(school-code LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra")

#set(CMAKE_C_FLAGS "-Wall -Wextra -O0 -S -masm=intel")

#add_executable(school-code main.c chapter_01.c chapter_02.c chapter_03.c chapter_04.c chapter_05.c
#  chapter_06.c chapter_07.c chapter_08.c chapter_09.c chapter_10.c library.c)

aux_source_directory(. SRC_LIST)
aux_source_directory(./KR SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
