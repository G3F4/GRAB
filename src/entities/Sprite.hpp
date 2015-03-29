/* Sprite class header */
#ifndef SPRITE_H_DEFINED
#define SPRITE_H_DEFINED

#include <SDL2/SDL.h>            // SDL2

#include <iostream>
#include <string>

#include "../singletons/Application.hpp"
#include "common/Texture.hpp"

class Sprite: public Texture {
public:
    Sprite(std::string ID,
        std::string file = "",
        int x = 0,
        int y = 0,
        int width = 0,
        int height = 0,
        std::string window_ID = "default",
        bool state = true);
protected:
    virtual bool load();
private:
    std::string m_file; /* string storing file name with extension */

};



#endif