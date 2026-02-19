cmake_minimum_required(VERSION 3.31.0)

option(BUILD_EDITOR "Build with editor functionality" ON)

project(Pudding CXX)

find_package(glad REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(flatbuffers REQUIRED)

add_executable(Pudding src/main.cpp
src/graphics/opengl/pgl_pipeline.cpp
src/game/routine/routine.cpp
src/graphics/opengl/pgl_pipeline.cpp
src/backends/imgui_impl_glfw.cpp
src/backends/imgui_impl_opengl3.cpp
src/gamefile/gamefile.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    message(STATUS "Debug mode is ON")
endif()

target_link_libraries(Pudding PRIVATE glfw)
target_link_libraries(Pudding PRIVATE glad::glad)
target_link_libraries(Pudding PRIVATE flatbuffers::flatbuffers)
target_link_libraries(Pudding PRIVATE imgui::imgui)

target_include_directories(Pudding PRIVATE src src/flatbuf)
target_include_directories(Pudding PRIVATE ${glad_INCLUDE_DIRS_DEBUG})

set_target_properties(Pudding PROPERTIES CXX_STANDARD 20)

include_directories(${GLAD_INCLUDE_DIRS})