#include "../../singletons/Application.hpp"
#include "Texture.hpp"

/* Texture Constructor
 * The most important things to remember when creating Texture object is:
 * - get decent id. It's used as handle to your object
 * - get the filename with proper extension - that's when you put your files where the framework folder is set. The
 *   default path is : "ProjectName/assets/images/" but you can always change it with Application instance method.
 * - 3rd and 4th parameters are position of left-upper corner of the window ( x and y )
 * - 5th and 6th parameters are dimensions of object. ( width and height )
 * */
Texture::Texture(std::string ID, int x, int y, int width, int height, std::string window_ID, bool state):
                BaseObject(ID,x,y,width,height,state)
{
    m_texture = nullptr;
    m_format = SDL_PIXELFORMAT_UNKNOWN;
    m_access = SDL_TEXTUREACCESS_TARGET;
    m_angle = 0.0;
    m_alpha = 255;
    m_flip = SDL_FLIP_NONE;
    m_window_ID = window_ID;
    m_pivot_point.x = m_box.w / 2;
    m_pivot_point.y = m_box.h / 2;
     // has to be called always after initialization of ALL FIELDS!!
    load();
}

bool Texture::load() {
    if (m_window_ID == "default") {
        m_window_ID = Application::Instance().get_default_window()->get_ID();
    }
    if (m_texture == SDL_CreateTexture(Application::Instance().get_window(m_window_ID)->get_renderer(), m_format, m_access, m_box.w, m_box.h)) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Texture Created. " << \
    " | box (x, y): (" << m_box.x << ", " << m_box.y << ") | box (w,h): (" << m_box.w << ", " << m_box.h << ")" << \
    " | format: " << m_format << \
    // #TODO check why getting format doesn't work
    " | access: " << m_access << std::endl;
    // #TODO check why getting access doesn't work
    set_blend_mode(SDL_BLENDMODE_BLEND);
    return true;
}

void Texture::render() {
    SDL_RenderCopyEx(Application::Instance().get_window(m_window_ID)->get_renderer(), m_texture, NULL, &m_box, m_angle, &m_pivot_point, m_flip);
}

void Texture::flip_vertiacally() {
    if ( m_flip == SDL_FLIP_NONE ) {
        m_flip = SDL_FLIP_VERTICAL;
    } else if ( m_flip == SDL_FLIP_VERTICAL ) {
        m_flip = SDL_FLIP_NONE;
    } else if ( m_flip == SDL_FLIP_HORIZONTAL ) {
        m_flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
}

void Texture::flip_horizontally() {
    if (m_flip == SDL_FLIP_NONE) {
        m_flip = SDL_FLIP_HORIZONTAL;
    } else if ( m_flip == SDL_FLIP_HORIZONTAL ) {
        m_flip = SDL_FLIP_NONE;
    } else if ( m_flip == SDL_FLIP_VERTICAL ) {
        m_flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
}

void Texture::rotate(int angle) {
    set_angle(get_angle() + angle);
}

void Texture::set_alpha(Uint8 alpha) {
    m_alpha = alpha;
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

Uint8 Texture::get_alpha() {
    return m_alpha;
}

void Texture::set_color_modulation(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( m_texture, red, green, blue );
}

void Texture::set_blend_mode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode( m_texture, blending );
}
