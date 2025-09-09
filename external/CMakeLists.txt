cmake_minimum_required(VERSION 3.26)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# === Project-wide switches ====================================================
# Select OpenGL loader set (matches your pre-generated GLAD trees)
set(SAGARDO_GL_API "43" CACHE STRING "OpenGL loader set: 33 or 43")
set_property(CACHE SAGARDO_GL_API PROPERTY STRINGS 33 43)

option(SAGARDO_ENABLE_VK "Enable Vulkan backend (volk + Vulkan-Headers)" OFF)

# GLFW: disable extras
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ZLIB OFF CACHE INTERNAL "" FORCE) # we provide zlib

# Freetype (lean)
set(FT_WITH_BROTLI   OFF CACHE BOOL "" FORCE)
set(FT_WITH_BZIP2    OFF CACHE BOOL "" FORCE)
set(FT_WITH_HARFBUZZ OFF CACHE BOOL "" FORCE)
set(FT_WITH_PNG      OFF CACHE BOOL "" FORCE)
set(FT_WITH_ZLIB     ON  CACHE BOOL "" FORCE) # hook into our zlib

# flecs: ensure static
set(FLECS_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(FLECS_BUILD_STATIC ON  CACHE BOOL "" FORCE)
set(FLECS_SHARED       OFF CACHE BOOL "" FORCE)
set(FLECS_STATIC       ON  CACHE BOOL "" FORCE)
add_compile_definitions(FLECS_STATIC)

# === FetchContent declarations ===============================================
FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.1.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# zlib first; used by assimp/freetype
FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-13-3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        filewatch
        GIT_REPOSITORY https://github.com/drsnuggles8/filewatch.git
        GIT_TAG master          # TODO: pin to a commit for reproducibility
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics
        GIT_TAG v5.3.0
        SOURCE_SUBDIR Build
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master          # TODO: pin to a commit for reproducibility
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

# Tracy profiler (headers + client)
FetchContent_Declare(
        Tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy
        GIT_TAG v0.12.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
set(TRACY_ON_DEMAND ON CACHE BOOL "" FORCE)

# Vulkan (optional)
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
FetchContent_MakeAvailable(flecs glm glfw)
FetchContent_MakeAvailable(zlib)
FetchContent_MakeAvailable(assimp freetype)
FetchContent_MakeAvailable(JoltPhysics stb filewatch Tracy)
if(SAGARDO_ENABLE_VK)
    FetchContent_MakeAvailable(VulkanHeaders volk_src)
endif()

# === Normalize targets / provide stable aliases ==============================
# glfw
if(TARGET glfw AND NOT TARGET glfw::glfw)
    add_library(glfw::glfw ALIAS glfw)
endif()

# assimp
if(TARGET assimp AND NOT TARGET assimp::assimp)
    add_library(assimp::assimp ALIAS assimp)
endif()

# zlib
if(NOT TARGET ZLIB::ZLIB)
    if(TARGET zlib)
        add_library(ZLIB::ZLIB ALIAS zlib)
    elseif(TARGET zlibstatic)
        add_library(ZLIB::ZLIB ALIAS zlibstatic)
    endif()
endif()

# glm (prefer glm::glm; also provide plain glm alias)
if(TARGET glm::glm)
    if(NOT TARGET glm)
        add_library(glm INTERFACE)
        target_link_libraries(glm INTERFACE glm::glm)
    endif()
else()
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE "${glm_SOURCE_DIR}")
endif()

# flecs
if(NOT TARGET flecs::flecs_static)
    if(TARGET flecs_static)
        add_library(flecs::flecs_static ALIAS flecs_static)
    elseif(TARGET flecs)
        add_library(flecs::flecs_static ALIAS flecs)
    endif()
endif()

# Freetype
if(TARGET freetype AND NOT TARGET Freetype::Freetype)
    add_library(Freetype::Freetype ALIAS freetype)
endif()

# Jolt
if(TARGET Jolt AND NOT TARGET Jolt::Jolt)
    add_library(Jolt::Jolt ALIAS Jolt)
endif()

# === GLAD selector (pre-generated trees under external/glad/...) =============
# GL 4.3
add_library(glad2_gl43 STATIC "${CMAKE_CURRENT_LIST_DIR}/glad/src/gl.c")
target_include_directories(glad2_gl43 PUBLIC "${CMAKE_CURRENT_LIST_DIR}/glad/include")
set_property(TARGET glad2_gl43 PROPERTY C_STANDARD 11)
target_compile_definitions(glad2_gl43 PUBLIC SAGARDO_GL43=1)
if(UNIX)
    set_target_properties(glad2_gl43 PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# GL 3.3 (uncomment if present)
# add_library(glad2_gl33 STATIC "${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/src/glad.c")
# target_include_directories(glad2_gl33 PUBLIC "${CMAKE_CURRENT_LIST_DIR}/glad/glad_gl33/include")
# set_property(TARGET glad2_gl33 PROPERTY C_STANDARD 11)
# target_compile_definitions(glad2_gl33 PUBLIC SAGARDO_GL33=1)
# if(UNIX)
#   set_target_properties(glad2_gl33 PROPERTIES POSITION_INDEPENDENT_CODE ON)
# endif()

# Choose the real implementation target
set(GLAD_SELECTED_TARGET glad2_gl43)
if(SAGARDO_GL_API STREQUAL "33")
    set(GLAD_SELECTED_TARGET glad2_gl33)
    message(STATUS "[deps] GL loader: glad2_gl33 selected")
else()
    message(STATUS "[deps] GL loader: glad2_gl43 selected")
endif()

# Create aliases that point to the REAL target (not an alias)
add_library(glad2 ALIAS ${GLAD_SELECTED_TARGET})
add_library(glad::glad ALIAS ${GLAD_SELECTED_TARGET})

# === stb_image implementation TU ============================================
# Your TU lives at external/stb/stb_image_impl.cpp and includes "stb_image.h".
add_library(stb_image STATIC
        "${CMAKE_CURRENT_LIST_DIR}/stb/stb_image_impl.cpp"
        "${stb_SOURCE_DIR}/stb_image.h"
)
target_include_directories(stb_image PUBLIC "${stb_SOURCE_DIR}")
if(UNIX)
    set_target_properties(stb_image PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# === filewatch (header-only) =================================================
# Adjust path if repo structure differs.
add_library(FileWatch INTERFACE)
target_include_directories(FileWatch INTERFACE "${filewatch_SOURCE_DIR}/include")

# --- Tracy client (prefer upstream target if it exists) ----------------------
# After FetchContent_MakeAvailable(Tracy)

if(TARGET TracyClient)
    # Upstream already defined it (static lib). Just alias it for stable naming.
    if(NOT TARGET Tracy::Client)
        add_library(Tracy::Client ALIAS TracyClient)
    endif()
    if(UNIX)
        # Ensure it’s usable in shared consumers if needed
        set_target_properties(TracyClient PROPERTIES POSITION_INDEPENDENT_CODE ON)
    endif()
else()
    # Some configurations don’t define a client lib: create a minimal OBJECT lib
    add_library(TracyClient OBJECT "${Tracy_SOURCE_DIR}/public/TracyClient.cpp")
    target_include_directories(TracyClient PUBLIC "${Tracy_SOURCE_DIR}/public")
    if(UNIX)
        set_target_properties(TracyClient PROPERTIES POSITION_INDEPENDENT_CODE ON)
    endif()
    add_library(Tracy::Client ALIAS TracyClient)
endif()


# === Vulkan / volk (optional) ================================================
if(SAGARDO_ENABLE_VK)
    add_library(volk STATIC "${volk_src_SOURCE_DIR}/volk.c")
    target_include_directories(volk PUBLIC
            "${volk_src_SOURCE_DIR}"
            "${VulkanHeaders_SOURCE_DIR}/include")
    target_compile_definitions(volk PUBLIC VOLK_STATIC_DEFINE VK_NO_PROTOTYPES)
    if(UNIX AND NOT APPLE)
        target_link_libraries(volk PRIVATE dl)
    endif()
    if(UNIX)
        set_target_properties(volk PROPERTIES POSITION_INDEPENDENT_CODE ON)
    endif()
endif()

message(STATUS "[deps] Third-party fetch/build complete")
