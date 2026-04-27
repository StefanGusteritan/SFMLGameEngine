cmake_minimum_required(VERSION 3.10)
project(GameEngine)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(Game)

# Define Source Files
set(SOURCES
    Example/main.cpp
    Example/TestGame.cpp
    Game/Game.cpp
    Game/Logger.cpp
    Game/Object.cpp
    Game/Scene.cpp
    Game/TimeManager.cpp
)

# Create Executable
add_executable(TestGame ${SOURCES})

# Windows-specific: Direct output to a 'Release' folder in a way that works for both Linux and MSVC
if(MSVC)
    # Visual Studio adds its own /Debug or /Release subfolder, so we set the base
    set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release")
    set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug")
else()
    set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")
endif()

# Link SFML libraries using the modern sfml:: namespace
# This is much better for Windows as it handles Debug/Release suffixes automatically
target_link_libraries(TestGame sfml-graphics sfml-window sfml-system sfml-audio)
