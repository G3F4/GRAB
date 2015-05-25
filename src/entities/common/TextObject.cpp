#include "TextObject.hpp"

TextObject::TextObject(std::string ID, std::string text, int x, int y, std::string font, SDL_Color color,
                       std::string window_ID): Texture(ID, x, y, 1, 1), m_text(text) {
    m_font = font.empty() ? TextManager::Instance().get_default_font() : TextManager::Instance().get_font(font);
    m_color = color;
    m_window_ID = window_ID.empty() ? Application::Instance().get_default_window()->get_ID() : window_ID;
    if (m_font && create()) {
        std::cout << "TextObject created." << std::endl;
    } else {
        std::cout << "Font error. Unable to create TextObject with ID: " << m_ID << std::endl;
    }
}

bool TextObject::create() {
    SDL_Surface *surf = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
    if (surf == NULL) {
        std::cout << TTF_GetError() << std::endl;
        return false;
    }
    m_texture = SDL_CreateTextureFromSurface(Application::Instance().get_default_window()->get_renderer(), surf);
    if (m_texture == NULL) {
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    SDL_QueryTexture(m_texture, NULL, NULL, &m_box.w, &m_box.h);
    set_size(m_size);
    return true;
}

void TextObject::set_font(std::string ID) {
    m_font = TextManager::Instance().get_font(ID);
    create();
}

void TextObject::set_color(std::string ID) {
    m_color = TextManager::Instance().get_color(ID);
    create();
}

void TextObject::set_color(SDL_Color color) {
    m_color = color;
    create();
}

void TextObject::set_color(Uint8 R, Uint8 G, Uint8 B) {
    m_color = {R, G, B};
    create();
}

TextObject &TextObject::set_size(int size) {
    //TTF_SizeText(m_font, m_text, )
    return *this;
}

void TextObject::set_text(std::string text) {
    m_text = text;
    create();
}
