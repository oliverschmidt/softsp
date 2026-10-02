set(PROJECT_NAME softSP)
cmake_minimum_required(VERSION 3.13...3.27)

include(FetchContent)
FetchContent_Declare(a2pico
        GIT_REPOSITORY https://github.com/oliverschmidt/a2pico.git
        GIT_TAG main
        )
FetchContent_MakeAvailable(a2pico)

include(pico_sdk_import.cmake)
project(${PROJECT_NAME} C CXX ASM)
pico_sdk_init()

add_executable(${PROJECT_NAME})
pico_add_extra_outputs(${PROJECT_NAME})

include(ExternalProject)
ExternalProject_Add(ProtocolConverter
        GIT_REPOSITORY https://github.com/btb/ProtocolConverter.git
        GIT_TAG main
        SOURCE_DIR ProtocolConverter
        BUILD_IN_SOURCE true
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND make -C src SoftSP-Grappler_S6.bin
        INSTALL_COMMAND ""
        )

set_source_files_properties(incbin.S
        OBJECT_DEPENDS ProtocolConverter
        )

target_sources(${PROJECT_NAME} PRIVATE
        incbin.S
        main.c
        )

target_link_libraries(${PROJECT_NAME} PRIVATE
        a2pico
        pico_stdlib
        )
