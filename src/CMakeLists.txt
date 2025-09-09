# Subprojects
add_subdirectory(Engine)

if(BUILD_TESTING)
    add_subdirectory(Engine.Tests)
endif()

if(BUILD_EDITOR)
    add_subdirectory(Editor)
endif()

if(BUILD_PLAYER)
    add_subdirectory(Player)
endif()