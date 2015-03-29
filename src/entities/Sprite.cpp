#include "Sprite.hpp"

bool Sprite::load() {
    if (m_window_ID == "default") {
        m_window_ID = Application::Instance().get_default_window()->get_ID();
    }
    m_texture = IMG_LoadTexture(Application::Instance().get_window(m_window_ID)->get_renderer(), m_file.c_str());
    if (m_texture == NULL) {
        std::cout << IMG_GetError() << std::endl;
        return false;
    } else {
        if (m_box.w == 0 || m_box.h == 0) {
            if ( SDL_QueryTexture(m_texture, &m_format, &m_access, &m_box.w, &m_box.h) != 0) {
                std::cout << SDL_GetError() << std::endl;
                SDL_ClearError();
            }
        } else {
            if ( SDL_QueryTexture(m_texture, &m_format, &m_access, NULL, NULL) != 0) {
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
        set_blend_mode(SDL_BLENDMODE_BLEND);
        return true;
    }

}

Sprite::Sprite(std::string ID, std::string file, int x, int y, int width, int height, std::string window_ID, bool state):
    Texture(ID, x, y, width, height, window_ID, state),
    m_file(file)
{
    if(!load()) {
        std::cout << "Couldn't create Sprite with ID: " << m_ID << std::endl;
        m_file = "../../assets/images/no-img.png";
        load();
    }
}
