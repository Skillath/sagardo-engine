include(FetchContent)
set(FETCHCONTENT_QUIET off)

# Define static linking for Flecs
add_compile_definitions(FLECS_STATIC)

# Flecs
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


FetchContent_Declare(
        filewatch
        GIT_REPOSITORY	https://github.com/drsnuggles8/filewatch.git
        GIT_TAG			master
        GIT_SHALLOW		TRUE
        GIT_PROGRESS TRUE
)
FetchContent_Declare(
        freetype
        GIT_REPOSITORY	https://github.com/freetype/freetype.git
        GIT_TAG			master
        GIT_SHALLOW		TRUE
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1
        GIT_SHALLOW		TRUE
        GIT_PROGRESS TRUE
)

# Include Jolt
FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics
        GIT_TAG v5.3.0
        SOURCE_SUBDIR Build
        GIT_SHALLOW		TRUE
        GIT_PROGRESS TRUE
)


# Grab the stb repo (pin a commit for reproducible builds).
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master       # TODO: pin a commit hash you trust
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(flecs)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(assimp)
FetchContent_MakeAvailable(zlib)    
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(freetype)
FetchContent_MakeAvailable(JoltPhysics)
FetchContent_MakeAvailable(stb)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_GetProperties(zlib)
set(ZLIB_LIBRARY_DEBUG "${zlib_BINARY_DIR}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}zlibd${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY_RELEASE "${zlib_BINARY_DIR}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}zlib${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY_DIST "${zlib_BINARY_DIR}/Dist/${CMAKE_STATIC_LIBRARY_PREFIX}zlib${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ZLIB_LIBRARY $<$<CONFIG:Debug>:${ZLIB_LIBRARY_DEBUG}>$<$<CONFIG:Release>:${ZLIB_LIBRARY_RELEASE}>$<$<CONFIG:Dist>:${ZLIB_LIBRARY_DIST}>)
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")
set(ZLIB_INCLUDE_DIRS "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")
set(ZLIB_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/zlib" "${CMAKE_CURRENT_BINARY_DIR}/zlib")

find_package(ZLIB REQUIRED)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ZLIB OFF CACHE INTERNAL "" FORCE)

add_library(Freetype::Freetype ALIAS freetype)


add_library(glad STATIC
        ${CMAKE_CURRENT_LIST_DIR}/glad/src/glad.c
)

target_include_directories(
        glad PUBLIC ${CMAKE_CURRENT_LIST_DIR}/glad/include)

# 3.2 Build a small lib that owns STB_IMAGE_IMPLEMENTATION
add_library(stb_image STATIC ${CMAKE_CURRENT_LIST_DIR}/stb/stb_image_impl.cpp)
# Expose the fetched include path to dependents
target_include_directories(stb_image PUBLIC ${stb_SOURCE_DIR})
# (We already defined STB_IMAGE_IMPLEMENTATION inside the TU; nothing here.)

#======================================
message(STATUS "Fetching third party libraries done")