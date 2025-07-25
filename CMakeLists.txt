cmake_minimum_required(VERSION 3.10)

set(PROJ_NAME "Simple RISC"     )   # this is implementation of simple RISC.
set(PROJ_LANG LANGUAGES C       )   # to be written in pure `C` no external libs.
set(PROJ_VERS VERSION  0.00.1   )   # need to make sure to change this version.
set(PROJ_DESC DESCRIPTION "stripped down implementation of riscV.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

# use de-oxygen for auto documentation from doc-strings.
find_package(Doxygen REQUIRED)
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/DOXYFILE     )
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/DOXYFILE    )
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target(DOCUMENTATION ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)

# every part of this project is standalone implementation there is to be no external or
# internal inter-executable dependencies, every (ASSEMBLER, DEBUGGER, SIMULATOR) are executable.
# each executable has its own purpose, and requires seperate implementation.

# SETUP ASSEMBLER `C` FOR ASSEMBLING RISC V SOURCE CODE
set(ASSEMBLER_SRC_DIR "${CMAKE_SOURCE_DIR}/assembler/source"    )
set(ASSEMBLER_INC_DIR "${CMAKE_SOURCE_DIR}/assembler/include"   )
file(GLOB ASSEMBLER_FILES "${ASSEMBLER_SRC_DIR}/*.c" "${ASSEMBLER_INC_DIR}/*.h")

add_executable(ASSEMBLER ${ASSEMBLER_FILES})
target_include_directories(ASSEMBLER PRIVATE ${ASSEMBLER_INC_DIR})

# SETUP SIMULATOR `C` TO RUN AND WATCH RISC V BYTE CODE
set(SIMULATOR_SRC_DIR "${CMAKE_SOURCE_DIR}/simulator/source"    )
set(SIMULATOR_INC_DIR "${CMAKE_SOURCE_DIR}/simulator/include"   )
file(GLOB SIMULATOR_FILES "${SIMULATOR_SRC_DIR}/*.c" "${SIMULATOR_INC_DIR}/*.h")

add_executable(SIMULATOR ${SIMULATOR_FILES})
target_include_directories(SIMULATOR PRIVATE ${SIMULATOR_INC_DIR})

# SETUP DEBUGGER `C` TO RUN AND WATCH RISC V DBG CODE
set(DEBUGGER_SRC_DIR "${CMAKE_SOURCE_DIR}/debugger/source"      )
set(DEBUGGER_INC_DIR "${CMAKE_SOURCE_DIR}/debugger/include"     )
file(GLOB DEBUGGER_FILES "${DEBUGGER_SRC_DIR}/*.c" "${DEBUGGER_INC_DIR}/*.h")

add_executable(DEBUGGER ${DEBUGGER_FILES})
target_include_directories(DEBUGGER PRIVATE ${DEBUGGER_INC_DIR})
