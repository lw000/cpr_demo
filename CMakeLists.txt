cmake_minimum_required(VERSION 3.27)
project(crp_demo)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(vcpkg_INCLUDE_DIRS ../../../scada_work/vcpkg/installed/x64-windows/include)
    set(vcpkg_LIBRARY ../../../scada_work/vcpkg/installed/x64-windows/debug/lib)

    message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
else ()
    set(vcpkg_INCLUDE_DIRS ../../../scada_work/vcpkg/installed/x64-windows/include)
    set(vcpkg_LIBRARY ../../../scada_work/work/vcpkg/installed/x64-windows/lib)

    message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
endif ()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -DNDEBUG")

include_directories(${vcpkg_INCLUDE_DIRS})

link_directories(${vcpkg_LIBRARY} ${leveldb_LIBRARY})

aux_source_directory(. SRCS_DIR)

add_executable(${PROJECT_NAME} main.cpp)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    target_link_libraries(${PROJECT_NAME} PRIVATE
            libcurl-d
            cpr
    )
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE
            libcurl
            cpr
    )
endif ()