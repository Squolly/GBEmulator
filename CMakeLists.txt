project(GameBoyEmulator) 

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(GAME_BOY_EMULATOR_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/Instruction.cpp
    ${PROJECT_SOURCE_DIR}/src/InstructionSet.cpp
    ${PROJECT_SOURCE_DIR}/src/InstructionSet_PrefixCB.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/LR35902.cpp
    ${PROJECT_SOURCE_DIR}/src/Memory.cpp
    ${PROJECT_SOURCE_DIR}/src/Registers.cpp
)

set(GAME_BOY_EMULATOR_HEADER_FILES
    ${PROJECT_SOURCE_DIR}/include/GBCartridge.hpp
    ${PROJECT_SOURCE_DIR}/include/GBRAM.hpp
    ${PROJECT_SOURCE_DIR}/include/GBROM.hpp
    ${PROJECT_SOURCE_DIR}/include/GBSound.hpp
    ${PROJECT_SOURCE_DIR}/include/GBVideo.hpp
    ${PROJECT_SOURCE_DIR}/include/Instruction.hpp
    ${PROJECT_SOURCE_DIR}/include/InstructionSet.hpp
    ${PROJECT_SOURCE_DIR}/include/InstructionSet_PrefixCB.hpp
    ${PROJECT_SOURCE_DIR}/include/Module.hpp
    ${PROJECT_SOURCE_DIR}/include/MemoryMappedModule.hpp
    ${PROJECT_SOURCE_DIR}/include/Memory.hpp
    ${PROJECT_SOURCE_DIR}/include/LR35902.hpp
    ${PROJECT_SOURCE_DIR}/include/Registers.hpp
    ${PROJECT_SOURCE_DIR}/include/types.hpp
)

add_executable(game_boy_emulator ${GAME_BOY_EMULATOR_SOURCE_FILES} ${GAME_BOY_EMULATOR_HEADER_FILES})
target_link_libraries(game_boy_emulator )
