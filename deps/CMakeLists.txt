include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# === Options used outside too (cache) ========================================
# Select GL loader set (matches your vendored folders)
set(SAGARDO_GL_API "43" CACHE STRING "OpenGL loader set: 33 or 43")
set_property(CACHE SAGARDO_GL_API PROPERTY STRINGS 33 43)

option(SAGARDO_ENABLE_VK "Enable Vulkan backend (volk + Vulkan-Headers)" OFF)

# GLFW: turn off extras
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ZLIB OFF CACHE INTERNAL "" FORCE) # we provide zlib

# Freetype: keep minimal
set(FT_WITH_BROTLI   OFF CACHE BOOL "" FORCE)
set(FT_WITH_BZIP2    OFF CACHE BOOL "" FORCE)
set(FT_WITH_HARFBUZZ OFF CACHE BOOL "" FORCE)
set(FT_WITH_PNG      OFF CACHE BOOL "" FORCE)
set(FT_WITH_ZLIB     ON  CACHE BOOL "" FORCE) # will hook to our zlib

# Global compile defs for flecs static
add_compile_definitions(FLECS_STATIC)

# === FetchContent declarations ===============================================

# flecs
FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.1.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# zlib (first; needed by assimp / freetype)
FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# assimp (needs zlib ready)
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# freetype (wants zlib too)
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-13-3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# filewatch
FetchContent_Declare(
        filewatch
        GIT_REPOSITORY https://github.com/drsnuggles8/filewatch.git
        GIT_TAG master
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

# stb (header-only; we add impl TU below)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master # consider pinning
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# Vulkan bits (optional): Vulkan-Headers + volk
if(SAGARDO_ENABLE_VK)
    FetchContent_Declare(
            VulkanHeaders
            GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
            GIT_TAG v1.3.296
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)

    FetchContent_Declare(
            volk_src
            GIT_REPOSITORY https://github.com/zeux/volk.git
            GIT_TAG v1.3.296
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)
endif()

# === MakeAvailable in safe order =============================================

# Always-safe header-only / libs
FetchContent_MakeAvailable(flecs glm glfw)

# zlib first
FetchContent_MakeAvailable(zlib)

# Tell consumers about zlib (targets: ZLIB::ZLIB)
# Newer zlib exports ZLIB::ZLIB target automatically when built as subproj.

# Now assimp + freetype (they will find/use zlib)
FetchContent_MakeAvailable(assimp freetype)

# Jolt, stb, filewatch
FetchContent_MakeAvailable(JoltPhysics stb filewatch)

# Vulkan headers + volk (optional)
if(SAGARDO_ENABLE_VK)
    FetchContent_MakeAvailable(VulkanHeaders volk_src)

    # Minimal volk target (use headers from Vulkan-Headers)
    add_library(volk STATIC "${volk_src_SOURCE_DIR}/volk.c")
    target_include_directories(volk PUBLIC
            "${volk_src_SOURCE_DIR}"
            "${VulkanHeaders_SOURCE_DIR}/include")
    # Static use + no prototypes (you must include <volk.h> before <vulkan/vulkan.h>)
    target_compile_definitions(volk PUBLIC VOLK_STATIC_DEFINE VK_NO_PROTOTYPES)
    # Linux needs dl for dynamic resolve
    if(UNIX AND NOT APPLE)
        target_link_libraries(volk PRIVATE dl)
    endif()
endif()

# Freetype alias (engine expects Freetype::Freetype)
add_library(Freetype::Freetype ALIAS freetype)

# === glad2 selection (your vendored pre-generated sets) ======================

# GL 4.3
add_library(glad2_gl43 STATIC
        "${CMAKE_CURRENT_LIST_DIR}/glad/src/gl.c")
target_include_directories(glad2_gl43 PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/glad/include")
set_property(TARGET glad2_gl43 PROPERTY C_STANDARD 11)
target_compile_definitions(glad2_gl43 PUBLIC SAGARDO_GL43=1)

# GL 3.3 (uncomment if you have this tree present)
#add_library(glad2_gl33 STATIC
#        "${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/src/glad.c")
#target_include_directories(glad2_gl33 PUBLIC
#        "${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/include")
#set_property(TARGET glad2_gl33 PROPERTY C_STANDARD 11)
#target_compile_definitions(glad2_gl33 PUBLIC SAGARDO_GL33=1)

# Create the selector alias `glad2`
if(SAGARDO_GL_API STREQUAL "33")
    add_library(glad2 ALIAS glad2_gl33)
    message(STATUS "[deps] GL loader: glad2_gl33 selected")
else()
    add_library(glad2 ALIAS glad2_gl43)
    message(STATUS "[deps] GL loader: glad2_gl43 selected")
endif()

# === stb_image implementation TU ============================================
add_library(stb_image STATIC "${stb_SOURCE_DIR}/stb_image.h" "${CMAKE_CURRENT_LIST_DIR}/stb/stb_image_impl.cpp")
target_include_directories(stb_image PUBLIC "${stb_SOURCE_DIR}")

message(STATUS "[deps] Third-party fetch/build complete")
