include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# ---------- Options that affect subprojects (must be set BEFORE MakeAvailable) ----------
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ZLIB OFF CACHE INTERNAL "" FORCE)

# ---------- Global compile defs ----------
add_compile_definitions(FLECS_STATIC)

# ---------- FetchContent declarations ----------
# flecs
FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.1.0
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE)

# glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE)

# glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE)

# assimp
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.2
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE)

# filewatch
FetchContent_Declare(
        filewatch
        GIT_REPOSITORY https://github.com/drsnuggles8/filewatch.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# freetype
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# zlib (assimp needs it but we're building our own)
FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# Jolt
FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics
        GIT_TAG v5.3.0
        SOURCE_SUBDIR Build
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# stb (header-only; we provide stb_image implementation TU)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master # TODO: pin a commit for deterministic builds
        GIT_SHALLOW TRUE)

# ---------- Fetch ----------
FetchContent_MakeAvailable(flecs)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(assimp)
FetchContent_MakeAvailable(zlib)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(freetype)
FetchContent_MakeAvailable(JoltPhysics)
FetchContent_MakeAvailable(stb)

# ---------- Zlib convenience (you had these; keeping them) ----------
FetchContent_GetProperties(zlib)
set(ZLIB_LIBRARY_DEBUG "${zlib_BINARY_DIR}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}zlibd${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY_RELEASE "${zlib_BINARY_DIR}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}zlib${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY_DIST "${zlib_BINARY_DIR}/Dist/${CMAKE_STATIC_LIBRARY_PREFIX}zlib${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY $<$<CONFIG:Debug>:${ZLIB_LIBRARY_DEBUG}>$<$<CONFIG:Release>:${ZLIB_LIBRARY_RELEASE}>$<$<CONFIG:Dist>:${ZLIB_LIBRARY_DIST}>)
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")
set(ZLIB_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/zlib" "${CMAKE_CURRENT_BINARY_DIR}/zlib")
find_package(ZLIB REQUIRED)

# ---------- Freetype alias ----------
add_library(Freetype::Freetype ALIAS freetype)

# ---------- glad2 (pre-generated, vendored) ----------
# Layout assumptions you told me:
#   deps/glad/include/glad/gl.h
#   deps/glad/src/gl.c
#   deps/glad/glad_gl33/include/glad/gl.h
#   deps/glad/glad_gl33/src/gl.c
option(USE_GLAD_GL43 "Use the GL 4.3 glad2 set in deps/glad" ON)

# GL 4.3 target
add_library(glad2_gl43 STATIC
        ${CMAKE_CURRENT_LIST_DIR}/glad/src/gl.c
)
target_include_directories(glad2_gl43 PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/glad/include
)
set_property(TARGET glad2_gl43 PROPERTY C_STANDARD 11)

## GL 3.3 target (fallback / portability)
#add_library(glad2_gl33 STATIC
#        ${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/src/glad.c
#)
#target_include_directories(glad2_gl33 PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/include
#)
#set_property(TARGET glad2_gl33 PROPERTY C_STANDARD 11)

#if (USE_GLAD_GL43)
#    add_library(glad2 ALIAS glad2_gl43)
#    add_compile_definitions(SAGARDO_GL43=1)
#else()
#    add_library(glad2 ALIAS glad2_gl33)
#    add_compile_definitions(SAGARDO_GL33=1)
#endif()
    add_library(glad2 ALIAS glad2_gl43)
    add_compile_definitions(SAGARDO_GL43=1)
# ---------- stb_image implementation TU ----------
add_library(stb_image STATIC ${CMAKE_CURRENT_LIST_DIR}/stb/stb_image_impl.cpp)
target_include_directories(stb_image PUBLIC ${stb_SOURCE_DIR})

message(STATUS "Fetching third party libraries done")