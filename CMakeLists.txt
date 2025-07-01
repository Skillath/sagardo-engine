cmake_minimum_required(VERSION 3.24...3.31.6)
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
  src/Engine/GameObject.hpp
  src/Engine/Scene.hpp
  src/Engine/Components.hpp
  src/Engine/IUpdatable.h)

add_library(${PROJECT_NAME}  
  src/main.cpp
  src/Engine/GameObject.cpp 
  src/Engine/Scene.cpp 
  src/Engine/GameObject.hpp
  src/Engine/Scene.hpp
  src/Engine/Components.hpp
  src/Engine/IUpdatable.h)

# Handle asset copying
file(GLOB ASSET_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/res/*")
foreach(ASSET_FILE ${ASSET_FILES})
  get_filename_component(ASSET_NAME ${ASSET_FILE} NAME)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/res/${ASSET_NAME}"
          "${CMAKE_CURRENT_BINARY_DIR}/res/${ASSET_NAME}")
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS} flecs::flecs_static) 
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES} flecs::flecs_static)


target_include_directories(${PROJECT_NAME}Exe PRIVATE ${raylib_INCLUDE_DIRS} flecs::flecs_static) 
target_link_libraries(${PROJECT_NAME}Exe PRIVATE ${raylib_LIBRARIES} flecs::flecs_static)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
