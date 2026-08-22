cmake_minimum_required(VERSION 3.15)
project(cppang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND MSVC)
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/windows_msvc)
    set(RAYLIB_LIB ${RAYLIB_DIR}/lib/raylib.lib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND MINGW)
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/windows_mingw)
    set(RAYLIB_LIB ${RAYLIB_DIR}/lib/libraylib.a)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/linux)
    set(RAYLIB_LIB ${RAYLIB_DIR}/lib/libraylib.a)
endif()

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE INC_FILES "${INCLUDE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE X11 GL m pthread dl)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include/GameStates include/Entities include/core include/helpers)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets to executable directory"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)