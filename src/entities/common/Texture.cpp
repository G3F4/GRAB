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
Texture::Texture(std::string ID, std::string file, int x, int y, int width, int height, std::string window_ID, bool state):
                BaseObject(ID,x,y,width,height,state), m_file(file)
{
    m_texture = nullptr;
    m_format = nullptr;
    m_access = nullptr;
    m_angle = 0.0;
    m_flip = SDL_FLIP_NONE;
    m_window_ID = window_ID;
    m_pivot_point.x = m_box.w / 2;
    m_pivot_point.y = m_box.h / 2;
     // has to be called always after initialization of ALL FIELDS!!
    if (!load()) {
        std::cout << "Texture " << m_ID << " not loaded." << std::endl;
    }
}

bool Texture::load() {
    if (m_window_ID == "default") {
        m_window_ID = Application::Instance().get_default_window()->get_ID();
    }
    m_texture = IMG_LoadTexture(Application::Instance().get_window(m_window_ID)->get_renderer(), m_file.c_str());
    if (m_texture == NULL) {
        std::cout << IMG_GetError() << std::endl;
        return false;
    } else {
        if (m_box.w == 0 || m_box.h == 0) {
            if ( SDL_QueryTexture(m_texture, m_format, m_access, &m_box.w, &m_box.h) != 0) {
                std::cout << SDL_GetError() << std::endl;
                SDL_ClearError();
            }
        } else {
            if ( SDL_QueryTexture(m_texture, m_format, m_access, NULL, NULL) != 0) {
                std::cout << SDL_GetError() << std::endl;
                SDL_ClearError();
            }
        }
        std::cout << "Texture loaded. Source:  " << m_file << \
        " | box (x, y): (" << m_box.x << ", " << m_box.y << ") | box (w,h): (" << m_box.w << ", " << m_box.h << ")" << \
        " | format: " << m_format << \
        // #TODO check why getting format doesn't work
        " | access: " << m_access << std::endl;
        // #TODO check why getting access doesn't work
        return true;
    }

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
