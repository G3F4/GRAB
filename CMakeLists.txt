# Clion cmake fileF
cmake_minimum_required(VERSION 2.8.4)
project(GRAB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add here all *.cpp files
set(SOURCE_FILES
    src/entities/base/BaseObject.cpp
    src/entities/Window.cpp
    src/entities/common/Texture.cpp
    src/entities/common/TextObject.cpp
    src/entities/Sprite.cpp

    src/singletons/Application.cpp
    src/singletons/TextureManager.cpp
    src/singletons/Events.cpp
    src/singletons/TextManager.cpp

    demo/main.cpp
    )

add_executable(GRAB ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
