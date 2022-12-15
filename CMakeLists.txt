CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
project(Game)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF ()

# Use C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics REQUIRED)

# Add include dirs for SFML
include_directories(/Library/Frameworks/SFML.framework/Headers)

add_library(Logic STATIC
        src/util/Stopwatch.cpp
        src/util/Stopwatch.h
        src/util/json.hpp

        src/model/World.cpp
        src/model/World.h
        src/model/Camera.cpp
        src/model/Camera.h
        src/model/Entity.h
        src/model/Player.cpp
        src/model/Player.h
        src/model/Wall.cpp
        src/model/Wall.h
        src/model/Goal.cpp
        src/model/Goal.h
        src/model/ConcreteFactory.cpp
        src/model/ConcreteFactory.h
        )

add_library(View STATIC
        src/view/EntityView.cpp
        src/view/EntityView.h
        )

add_executable(Game
        src/main.cpp

        src/controller/Game.cpp
        src/controller/Game.h
        src/controller/StateManager.cpp
        src/controller/StateManager.h
        src/controller/AbstractFactory.h
        )

# Link target to SFML libs
target_link_libraries(View sfml-system sfml-graphics sfml-window)
target_link_libraries(Logic sfml-system sfml-graphics sfml-window)
target_link_libraries(Game Logic View sfml-system sfml-graphics sfml-window)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
install(TARGETS Game DESTINATION bin)
