cmake_minimum_required(VERSION 2.6)
project(tylang)

set(tylang_VERSION_MAJOR 0)
set(tylang_VERSION_MINOR 2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)

include_directories(.)
include_directories(../external)

# common
file(GLOB tycommon_src ./common/*.cpp)
file(GLOB tycommon_hdr ./common/*.h)
add_library(tycommon STATIC ${tycommon_src} ${tycommon_hdr}) 

# token
file(GLOB tytoken_src ./token/*.cpp)
file(GLOB tytoken_hdr ./token/*.h)
add_library(tytoken STATIC ${tytoken_src} ${tytoken_hdr}) 

# parse
file(GLOB typarse_src ./parse/*.cpp)
file(GLOB typarse_hdr ./parse/*.h)
add_library(typarse STATIC ${typarse_src} ${typarse_hdr}) 

# cgen
file(GLOB tycgen_src ./cgen/*.cpp)
file(GLOB tycgen_hdr ./cgen/*.h)
add_library(tycgen STATIC ${tycgen_src} ${tycgen_hdr}) 


# ty_dev_console
file(GLOB ty_dev_console_src ./dev_console/*.cpp)
add_executable(tyd ${ty_dev_console_src})
target_link_libraries(tyd tycommon typarse tycgen tytoken)

# gtest
file(GLOB gtest_src ./gtest/*.cc)
file(GLOB gtest_hdr ./gtest/*.h)
add_library(gtest STATIC ${gtest_src} ${gtest_hdr})

# unit tests
file(GLOB unit_tests_src ./unit_tests/*.cpp)
add_executable(ty_unit_tests ${unit_tests_src})
target_link_libraries(ty_unit_tests tycommon typarse tycgen tytoken gtest)
target_include_directories(ty_unit_tests PRIVATE ../src/gtest)

add_custom_command(TARGET ty_unit_tests POST_BUILD COMMAND "$(TargetDir)$(TargetFileName)\nexit 0")
