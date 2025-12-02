cmake_minimum_required(VERSION 3.30)

project(newproject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


message(STATUS "-----------------Build type: ${CMAKE_BUILD_TYPE}------------")

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wdouble-promotion
        -Wno-sign-conversion
        -Wignored-qualifiers
        -Wsuggest-attribute=const
        -Wsuggest-attribute=pure
        -Wcast-qual

    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring with sanitisers for Debug build")

    if(MSVC)
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.28)
            add_compile_options(/fsanitize=address /fsanitize=undefined)
        else()
            message(WARNING "MSVC compiler version too old for sanitisers")
        endif()
    else()
        add_compile_options(
            -fsanitize=address
            -fsanitize=undefined
            -fsanitize=leak
            -fsanitize=float-divide-by-zero
            -fsanitize=null
            -fsanitize=alignment
            -fno-omit-frame-pointer
            -g3
        )
        add_link_options(
            -fsanitize=address
            -fsanitize=undefined
            -fsanitize=leak
        )
    endif()
else()
    message(STATUS "Configuring without sanitisers for ${CMAKE_BUILD_TYPE} build")
    if(NOT MSVC)
        add_compile_options(-O2 -DNDEBUG)
    endif()
endif()


include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp


)
