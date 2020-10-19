cmake_minimum_required(VERSION 3.1)

project(main)

find_library(CURSES_LIBRARY ncursesw)
find_library(PCRE_LIBRARY pcre2-8)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

option(UTF "Utf" ON)

if(UTF)
  add_definitions(-DUTF=0)
endif()

add_executable(main main.c pcre_util.c)

target_link_libraries(main ${CURSES_LIBRARY} ${PCRE_LIBRARY})
