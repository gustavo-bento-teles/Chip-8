cmake_minimum_required(VERSION 3.10)

project(Chip8 C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB SRC_FILES
    src/*.c
)

add_executable(chip8 ${SRC_FILES})

target_include_directories(chip8 PRIVATE
    src/include
)

if(WIN32)

    set(SDL_DIR ${CMAKE_SOURCE_DIR}/external/SDL2/windows)

    target_include_directories(chip8 PRIVATE
        ${SDL_DIR}/include
    )

    target_link_directories(chip8 PRIVATE
        ${SDL_DIR}/lib
    )

    target_link_libraries(chip8
    mingw32
    SDL2main
    SDL2
    )

    add_custom_command(TARGET chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_DIR}/bin/SDL2.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )

elseif(UNIX)

    set(SDL_DIR ${CMAKE_SOURCE_DIR}/external/SDL2/linux)

    target_include_directories(chip8 PRIVATE
        ${SDL_DIR}/include/SDL2
    )

    target_link_directories(chip8 PRIVATE
        ${SDL_DIR}/lib
    )

    target_link_libraries(chip8
        SDL2
    )

    set_target_properties(chip8 PROPERTIES
        BUILD_RPATH
        "$ORIGIN/../external/SDL2/linux/lib"
    )

endif()

if(MINGW)
    set_target_properties(chip8 PROPERTIES SUFFIX ".exe")
endif()

target_compile_options(chip8 PRIVATE
    -Wall
    -Wextra
    -g
)
