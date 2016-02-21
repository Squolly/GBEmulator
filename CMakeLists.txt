project(GameBoyEmulator) 

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(GAME_BOY_EMULATOR_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(game_boy_emulator ${GAME_BOY_EMULATOR_SOURCE_FILES})
target_link_libraries(game_boy_emulator )
