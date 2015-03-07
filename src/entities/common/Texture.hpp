#ifndef TEXTURE_H_DEFINED
#define TEXTURE_H_DEFINED

#include <SDL2/SDL.h>            // SDL2
#include <SDL2/SDL_image.h>      // SDL2_Image

#include <iostream>
#include <string>

#include "../base/BaseObject.hpp"


class Texture: public BaseObject {
public:
	Texture(std::string ID,
            std::string file = "",
            int x = 0,
            int y = 0,
            int width = 0,
            int height = 0,
            std::string window_ID = "default",
            bool state = true
    );
    void render(); /* render the Texture to it's window */
    SDL_Texture* get_texture(void) { return m_texture; } /* return pointer to SDL_Texture  */
    void set_texture(SDL_Texture* texture) { m_texture = texture; } /* set Texture object SDL_Texture structure */
    std::string get_file() { return m_file; } /* return source file name with extension */
    void set_file(std::string file) { m_file = file; } /* set source file for Texture object */
    std::string get_window_ID() { return m_window_ID; } /* return ID of which will render Texture */
    void set_window_ID(std::string ID) { m_window_ID = ID; } /* set ID of window which will render Texture */
    double get_angle() { return m_angle; } /* return texture angle */
    void set_angle(double angle) { m_angle = angle; } /* set angle of texture */
    SDL_Point get_pivot_point() { return m_pivot_point; } /* return pivot point */
    void set_pivot_point(SDL_Point pivot_point) { m_pivot_point = pivot_point; } /* set pivot point */
    void flip_horizontally(); /* flip Texture horizontally */
    void flip_vertiacally(); /* flip Texture vertically */
    void rotate(int angle); /* Passing positive value will rotate clockwise, negatice oposite */
    SDL_RendererFlip get_flip() { return m_flip; }
    void set_flip(SDL_RendererFlip flip) { m_flip = flip; }
    void set_alpha(Uint8 alpha);
    Uint8 get_alpha();
    //Set color modulation
    void set_color_modulation( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void set_blend_mode( SDL_BlendMode blending );
private:
    bool load(); /* method responsible */
	std::string m_file;
    SDL_Texture* m_texture;
    std::string m_window_ID; // ID of window to render
    double m_angle; // #TODO add angle, flip and pivot point functionality
    SDL_Point m_pivot_point ;
    SDL_RendererFlip m_flip;
    Uint32* m_format;
    int* m_access;
    Uint8 m_alpha;
};

#endif /* TEXTURE_H_DEFINED */
