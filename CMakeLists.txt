cmake_minimum_required(VERSION 3.26...3.31.6)

project(SagardoEngine VERSION 0.0.1 LANGUAGES C CXX)

# ---------- Global ----------
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Static libs may be linked into shared/lib later (plugins), keep PIC on
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_EDITOR "Build the Editor executable" ON)
option(BUILD_PLAYER "Build the Player executable" ON)
option(BUILD_TESTING "Enable building tests (CTest)" ON)


option(SAGARDO_BUILD_EDITOR "Build the Editor executable" ON)
option(SAGARDO_BUILD_PLAYER "Build the Player executable" ON)
option(BUILD_TESTING "Enable CTest" ON)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
  include(CTest)
endif()

add_subdirectory(external EXCLUDE_FROM_ALL) # third-party
add_subdirectory(src)                       # engine + apps


add_executable(${PROJECT_NAME}.Main 
        src/main.cpp)