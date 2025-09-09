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