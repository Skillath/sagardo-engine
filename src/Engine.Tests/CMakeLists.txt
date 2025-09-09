set(ENGINE_TARGET_TESTS SagardoEngine.Tests)

add_executable(${ENGINE_TARGET_TESTS}
        main.cpp
)
target_compile_features(${ENGINE_TARGET_TESTS} PRIVATE cxx_std_26)
target_link_libraries(${ENGINE_TARGET_TESTS} PRIVATE SagardoEngine)
add_test(NAME ${ENGINE_TARGET_TESTS} COMMAND ${ENGINE_TARGET_TESTS})
set_target_properties(${ENGINE_TARGET_TESTS} PROPERTIES FOLDER "Tests")