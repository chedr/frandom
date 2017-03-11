cmake_minimum_required(VERSION 2.8)
project(frandom)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

set(GENERAL_WARNING_FLAGS           "-Wall -Wextra -pedantic -Wundef -Wshadow -Wno-zero-length-array -Wno-cast-align -Wno-unused-parameter -Wno-unused-variable -Wcast-align -Wwrite-strings -Wswitch-default -Wswitch-enum -Wconversion -Wfloat-equal -Wno-aggregate-return")
set(GENERAL_DEBUG_FLAGS             "-ggdb -O0 -fno-omit-frame-pointer -fprofile-arcs -ftest-coverage -fsanitize=address")
set(GENERAL_RELEASE_FLAGS           "-DNDEBUG -O3 -fomit-frame-pointer -funswitch-loops")
set(GENERAL_COMPILER_FLAGS          "-pipe -mrdrnd")
set(STATIC_COMPILER_FLAGS           "-fPIC")

set(CMAKE_CXX_FLAGS_DEFAULT         "-std=c++11 -Weffc++ -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual -fnon-call-exceptions")
set(CMAKE_C_FLAGS_DEFAULT           "-std=c11")
set(CMAKE_EXE_LINKER_FLAGS_DEFAULT  "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "-rdynamic -fprofile-arcs -ftest-coverage -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE  "-s")

set(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS_DEFAULT} ${GENERAL_COMPILER_FLAGS} ${GENERAL_WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG_DEFAULT} ${GENERAL_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE_DEFAULT} ${GENERAL_RELEASE_FLAGS}")
set(CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS_DEFAULT} ${GENERAL_WARNING_FLAGS} ${GENERAL_COMPILER_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS_DEBUG_DEFAULT} ${GENERAL_DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE           "${CMAKE_C_FLAGS_RELEASE_DEFAULT} ${GENERAL_RELEASE_FLAGS}")

set(FRANDOM_SOURCE_DIR              "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(FRANDOM_INCLUDE_DIR             "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE FRANDOM_FILES_CXX "${FRANDOM_SOURCE_DIR}/*.cpp")

add_executable(frandom ${FRANDOM_FILES_CXX})
target_include_directories(frandom PUBLIC ${FRANDOM_INCLUDE_DIR})

install(TARGETS
        frandom
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)
