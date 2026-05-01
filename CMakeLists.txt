cmake_minimum_required(VERSION 3.10)
project(GameEngine)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Define Engine Library
set(ENGINE_SOURCES
    Game/Game.cpp
    Game/Logger.cpp
    Game/Object.cpp
    Game/Scene.cpp
    Game/TimeManager.cpp
)

add_library(Engine STATIC ${ENGINE_SOURCES})

# Link SFML to the Engine library
# PUBLIC ensures that anything linking to Engine also gets SFML
target_link_libraries(Engine PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)

# Set include directories for the Engine
# INTERFACE/PUBLIC means projects using the engine will automatically know where the headers are
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Game ${CMAKE_CURRENT_SOURCE_DIR})

# Only build the example if this is the top-level project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Define Example Source Files
    set(EXAMPLE_SOURCES
        Example/main.cpp
        Example/TestGame.cpp
    )

    # Create Executable (The Test Game)
    add_executable(TestGame ${EXAMPLE_SOURCES})
    set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY
             "${CMAKE_BINARY_DIR}/Release")
    target_link_libraries(TestGame Engine)
endif()
