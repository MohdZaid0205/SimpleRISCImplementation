cmake_minimum_required(VERSION 3.10)

set(PROJ_NAME "HMASM"           )   # this is implementation of assembler.
set(PROJ_LANG LANGUAGES C       )   # to be written in pure `C` no external libs.
set(PROJ_VERS VERSION  0.00.3   )   # need to make sure to change this version.
set(PROJ_DESC DESCRIPTION "stripped down implementation of assembler.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})


# For predefined targets put them all into a folder (if possible)
foreach(predef_target ALL_BUILD ZERO_CHECK INSTALL PACKAGE RUN_TESTS)
    if(TARGET ${predef_target})
        set_target_properties(${predef_target} PROPERTIES FOLDER "CMake Predefined Targets")
    endif()
endforeach()

