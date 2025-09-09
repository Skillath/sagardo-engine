set(PLAYER_TARGET SagardoEngine.Player)

add_executable(${PLAYER_TARGET}
        main.cpp
)
target_compile_features(${PLAYER_TARGET} PRIVATE cxx_std_26)
target_link_libraries(${PLAYER_TARGET} PRIVATE SagardoEngine)

add_custom_command(TARGET ${PLAYER_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/res"
        "$<TARGET_FILE_DIR:${PLAYER_TARGET}>/res"
)
set_target_properties(${PLAYER_TARGET} PROPERTIES FOLDER "Apps/Player")