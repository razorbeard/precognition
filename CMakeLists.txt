cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PRECOGNITION)

# Add External Dependencies
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_NETWORK OFF)
FetchContent_Declare(
   SFML
   GIT_REPOSITORY https://github.com/SFML/SFML.git
   GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_custom_target(
    copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/resources
)

file(GLOB_RECURSE SOURCES src/*.cpp "include/*.hpp")
add_executable(PRECOGNITION ${SOURCES})
add_dependencies(PRECOGNITION copy_resources)
target_include_directories(PRECOGNITION PUBLIC "include")
target_link_libraries(PRECOGNITION PRIVATE sfml-graphics)

install(TARGETS PRECOGNITION)
