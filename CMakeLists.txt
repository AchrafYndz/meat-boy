CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
project(2022-project-AchrafYndz)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF ()

# Use C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# The source files to compile
SET(SRC
        src/main.cpp

        src/util/Stopwatch.cpp
        src/util/Stopwatch.h
        src/util/json.hpp

        src/view/EntityView.cpp
        src/view/EntityView.h

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

        src/controller/Game.cpp
        src/controller/Game.h
        src/controller/StateManager.cpp
        src/controller/StateManager.h
        src/controller/AbstractFactory.h
        )

# Add include dirs for SFML
INCLUDE_DIRECTORIES(/Library/Frameworks/SFML.framework/Headers)

# The program we're compiling with the sources set above
ADD_EXECUTABLE(game ${SRC})

# Link target to SFML libs
TARGET_LINK_LIBRARIES(game sfml-system sfml-graphics sfml-window)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
INSTALL(TARGETS game DESTINATION bin)
