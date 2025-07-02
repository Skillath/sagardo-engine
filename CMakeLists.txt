cmake_minimum_required(VERSION 3.26...3.31.6)
include(GenerateExportHeader)
project(CiderEngine)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23) # Requires C11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

find_package(flecs REQUIRED)

add_executable(${PROJECT_NAME}Exe 
        src/main.cpp
        src/Engine/GameObject.cpp
        src/Engine/Scene.cpp
        src/Engine/GameObject.h
        src/Engine/Scene.h
        src/Engine/Components.h
        src/Engine/IUpdatable.h
        src/Engine/IStartable.h
        src/Engine/IStopable.h
        src/Engine/RenderPipeline.cpp
        src/Engine/RenderPipeline.h
)

add_library(${PROJECT_NAME}  
        src/main.cpp
        src/Engine/GameObject.cpp
        src/Engine/Scene.cpp
        src/Engine/GameObject.h
        src/Engine/Scene.h
        src/Engine/Components.h
        src/Engine/IUpdatable.h
        src/Engine/IStartable.h
        src/Engine/IStopable.h
        src/Engine/RenderPipeline.cpp
        src/Engine/RenderPipeline.h
        src/Engine/IRenderPipeline.h
)


target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS} flecs::flecs_static) 
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES} flecs::flecs_static)

target_include_directories(${PROJECT_NAME}Exe PRIVATE ${raylib_INCLUDE_DIRS} flecs::flecs_static) 
target_link_libraries(${PROJECT_NAME}Exe PRIVATE ${raylib_LIBRARIES} flecs::flecs_static)


# copy assets
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/src/res
        ${CMAKE_CURRENT_BINARY_DIR}/src/res
        COMMENT "Smart-copying changed asset files"
)

add_dependencies(${PROJECT_NAME} copy_assets)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
