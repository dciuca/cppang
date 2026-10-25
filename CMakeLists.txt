cmake_minimum_required(VERSION 3.15)
project(cppang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- RAYLIB ---
# Use FetchContent for Windows to automatically build raylib from source
# This ensures compatibility with your Visual Studio version
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(FetchContent)

    set(BUILD_EXAMPLES OFF CACHE INTERNAL "Don't build raylib examples")
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build raylib as static library")

    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(raylib)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Use pre-built static library for Linux
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/linux)
    set(RAYLIB_LIB ${RAYLIB_DIR}/lib/libraylib.a)
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${RAYLIB_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
    )

endif()

# --- SOURCES ---
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE INC_FILES "${INCLUDE_DIR}/*.h")

# --- MAIN TARGET ---
add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/GameStates 
    include/Entities 
    include/core 
    include/helpers
)

# Copy assets to the executable directory after build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets to executable directory"
)

# set_target_properties(${PROJECT_NAME} PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
# )

# # --- TEST TARGET ---
# # Filter out main.cpp from the game sources to avoid duplicate main function
# file(GLOB_RECURSE GAME_SRC_FILES "${SOURCE_DIR}/*.cpp")
# list(FILTER GAME_SRC_FILES EXCLUDE REGEX ".*main\\.cpp$")

# # Create test executable with the test file and all game sources (excluding main)
# add_executable(test_level test/test_level.cpp ${GAME_SRC_FILES} ${INC_FILES})

# # Link raylib only - it handles all system dependencies internally
# target_link_libraries(test_level PRIVATE raylib)

# # Include directories for test target
# target_include_directories(test_level PRIVATE 
#     include/GameStates 
#     include/Entities 
#     include/core 
#     include/helpers
# )

# # Copy assets to the test executable directory
# add_custom_command(
#     TARGET test_level POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         "${CMAKE_SOURCE_DIR}/assets"
#         "$<TARGET_FILE_DIR:test_level>/assets"
#     COMMENT "Copying assets to test executable directory"
# )

# # Set working directory for debugging in Visual Studio
# set_target_properties(test_level PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
# )