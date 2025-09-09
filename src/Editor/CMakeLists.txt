set(EDITOR_TARGET SagardoEngine.Editor)

add_executable(${EDITOR_TARGET}
        main.cpp
)

target_compile_features(${EDITOR_TARGET} PRIVATE cxx_std_26)

target_link_libraries(${EDITOR_TARGET}
        PRIVATE SagardoEngine
)

# Copy assets beside the exe
add_custom_command(TARGET ${EDITOR_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/res"
        "$<TARGET_FILE_DIR:${EDITOR_TARGET}>/res"
)
set_target_properties(${EDITOR_TARGET} PROPERTIES FOLDER "Apps/Editor")

if(NOT GLAD_CUSTOM_OUTPUT)
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/bin/debug/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/bin/release/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/build/bin/MinSizeRel/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/bin/RelWithDebInfo/")
else()
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${GLAD_CUSTOM_OUTPUT_DEBUG}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${GLAD_CUSTOM_OUTPUT_RELEASE}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${GLAD_CUSTOM_OUTPUT_MINSIZEREL}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GLAD_CUSTOM_OUTPUT_RELWITHDEBINFO}")
endif()