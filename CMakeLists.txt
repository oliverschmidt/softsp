set(PROJECT_NAME Grappler-Plus)

cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(${PROJECT_NAME} C CXX ASM)
pico_sdk_init()

add_executable(${PROJECT_NAME})
pico_add_extra_outputs(${PROJECT_NAME})

set_source_files_properties(incbin.S
        OBJECT_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/grappler-plus.rom
        )

include(FetchContent)
FetchContent_Declare(a2pico
        GIT_REPOSITORY https://github.com/oliverschmidt/a2pico.git
        GIT_TAG main
        )
FetchContent_MakeAvailable(a2pico)

target_sources(${PROJECT_NAME} PRIVATE
        main.c
        incbin.S
        )

target_link_libraries(${PROJECT_NAME} PRIVATE
        pico_stdlib
        a2pico
        )
