cmake_minimum_required(VERSION 3.1)
project(GameBoyEmulator) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/FindSFML.cmake")
    find_package(SFML 2 REQUIRED COMPONENTS system window graphics audio) 
else()

endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    
    # SFML (optional) 
    ${SFML_INCLUDE_DIR}
)

find_package(Threads REQUIRED)

set(GAME_BOY_EMULATOR_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/GBCartridge.cpp
    ${PROJECT_SOURCE_DIR}/src/GBInterruptEnable.cpp
    ${PROJECT_SOURCE_DIR}/src/GBInterruptFlag.cpp
    ${PROJECT_SOURCE_DIR}/src/Sound/GBSound.cpp
    ${PROJECT_SOURCE_DIR}/src/Cartridge/GBMBC1.cpp
    ${PROJECT_SOURCE_DIR}/src/GBJoypad.cpp
    ${PROJECT_SOURCE_DIR}/src/GBRAM.cpp
    ${PROJECT_SOURCE_DIR}/src/GBROM.cpp
    ${PROJECT_SOURCE_DIR}/src/GBSerialTransfer.cpp
    ${PROJECT_SOURCE_DIR}/src/GBTimer.cpp
    ${PROJECT_SOURCE_DIR}/src/GBVideo.cpp
    ${PROJECT_SOURCE_DIR}/src/Instruction.cpp
    ${PROJECT_SOURCE_DIR}/src/InstructionSet.cpp
    ${PROJECT_SOURCE_DIR}/src/InstructionSet_PrefixCB.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/LR35902.cpp
    ${PROJECT_SOURCE_DIR}/src/Memory.cpp
    ${PROJECT_SOURCE_DIR}/src/Registers.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Utility/ScopedTimer.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Sound/Synth.cpp
)

set(GAME_BOY_EMULATOR_HEADER_FILES
    ${PROJECT_SOURCE_DIR}/include/GBCartridge.hpp
    ${PROJECT_SOURCE_DIR}/include/GBJoypad.hpp
    ${PROJECT_SOURCE_DIR}/include/GBInterruptEnable.hpp
    ${PROJECT_SOURCE_DIR}/include/GBInterruptFlag.hpp
    ${PROJECT_SOURCE_DIR}/include/Sound/GBSound.hpp
    ${PROJECT_SOURCE_DIR}/include/Sound/SquareWave.hpp
    ${PROJECT_SOURCE_DIR}/include/Cartridge/GBMBC1.hpp
    ${PROJECT_SOURCE_DIR}/include/GBRAM.hpp
    ${PROJECT_SOURCE_DIR}/include/GBROM.hpp
    ${PROJECT_SOURCE_DIR}/include/GBSerialTransfer.hpp
    ${PROJECT_SOURCE_DIR}/include/GBSound.hpp
    ${PROJECT_SOURCE_DIR}/include/GBTimer.hpp
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
    
    ${PROJECT_SOURCE_DIR}/include/Utility/ScopedTimer.hpp
    
    ${PROJECT_SOURCE_DIR}/include/Sound/Synth.hpp
    ${PROJECT_SOURCE_DIR}/include/Sound/SweepSquareWave.hpp
    ${PROJECT_SOURCE_DIR}/include/Sound/Wave.hpp
)

if(SFML_FOUND)
    set(GAME_BOY_EMULATOR_SOURCE_FILES 
        ${GAME_BOY_EMULATOR_SOURCE_FILES}
        ${PROJECT_SOURCE_DIR}/src/SFML_GBVideo.cpp
    )
    set(GAME_BOY_EMULATOR_HEADER_FILES
        ${GAME_BOY_EMULATOR_HEADER_FILES}
        ${PROJECT_SOURCE_DIR}/include/SFML_GBVideo.hpp
        ${PROJECT_SOURCE_DIR}/include/Sound/SFML_GBSound.hpp
    )
    
else(SFML_FOUND) 

endif(SFML_FOUND)

add_executable(game_boy_emulator ${GAME_BOY_EMULATOR_SOURCE_FILES} ${GAME_BOY_EMULATOR_HEADER_FILES})
target_link_libraries(game_boy_emulator ${SFML_LIBRARIES} Threads::Threads)
