project(GameBoyEmulator) 

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(GAME_BOY_EMULATOR_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/LR35902.cpp
    ${PROJECT_SOURCE_DIR}/src/Memory.cpp
    ${PROJECT_SOURCE_DIR}/src/Registers.cpp
)

set(GAME_BOY_EMULATOR_HEADER_FILES
#    ${PROJECT_SOURCE_DIR}/include/Memory.hpp
#   ${PROJECT_SOURCE_DIR}/include/Registers.hpp
    ${PROJECT_SOURCE_DIR}/include/types.hpp
     ${PROJECT_SOURCE_DIR}/include/Instruction.hpp
)

add_executable(game_boy_emulator ${GAME_BOY_EMULATOR_SOURCE_FILES} ${GAME_BOY_EMULATOR_HEADER_FILES})
target_link_libraries(game_boy_emulator )
