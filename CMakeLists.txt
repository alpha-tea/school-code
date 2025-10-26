cmake_minimum_required(VERSION 3.5)

project(school-code LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c11")

#set(CMAKE_C_FLAGS "-Wall -Wextra -O0 -S -masm=intel")

add_executable(school-code
  main.c
  chapter_01.c
  chapter_02.c
  chapter_03.c
  chapter_04.c
  chapter_05.c
  chapter_06.c
  chapter_07.c
  chapter_08.c
  chapter_09.c
  chapter_10.c
  chapter_11.c
  chapter_12.c
  chapter_16.c
  theory.c
  library.c
  games.c
  exam.c
  KernighanRitchie.c
  library.h
  )
