cmake_minimum_required(VERSION 4.0)

# Optionally set compilers BEFORE project() if you want to override defaults
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

project(windowCapture)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# our files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")

# external
file(GLOB_RECURSE EXTERNAL_SOURCES "external/src/*/*.cpp" "external/src/*/*.c")
file(GLOB_RECURSE EXTERNAL_HEADERS "external/include/*/*.h" "external/include/*/*.hpp")

# Combine source files
set(SOURCES ${SRC_FILES} ${EXTERNAL_SOURCES} ${EXTERNAL_HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES})
file(GLOB_RECURSE LIBBARYS "external/lib/*.dll" "external/lib/*.a")

# Link libraries (use .dll only for runtime, link .lib/.a for build)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIBBARYS}
    stdc++exp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
)