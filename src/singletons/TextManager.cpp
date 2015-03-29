#include "TextManager.hpp"

std::unique_ptr<TextManager> TextManager::m_instance;
std::once_flag TextManager::m_once_flag;

TextManager& TextManager::Instance() {
    std::call_once(m_once_flag, [] {
        m_instance.reset(new TextManager);
    });
    return *m_instance.get();
}

TextManager::TextManager(void) {
    m_font_folder = "assets/fonts/";
    std::cout << "TextManager singelton instantiated." << std::endl;
    if(TTF_Init() == -1) {
        std::cout << TTF_GetError() << std::endl;
    } else {
        std::cout << "TTF inited." << std::endl;
    }
    std::string font_path = m_font_folder + DEFAULT_FONT_FILE;
    m_fonts[DEFAULT_FONT_NAME] = TTF_OpenFont(font_path.c_str(), 16);
    if (m_fonts[DEFAULT_FONT_NAME] == NULL) {
        std::cout << TTF_GetError() << std::endl;
    } else {
        std::cout << "Default font loaded. Font name: " << DEFAULT_FONT_NAME << " | Font file: " << DEFAULT_FONT_FILE <<std::endl;
    }
    m_colors[DEFAULT_COLOR] = {0,0,0};
}

TextManager::~TextManager(void) {
    for (auto font : m_fonts) {
        TTF_CloseFont(m_fonts[font.first]);
        std::cout << font.first << " font closed." <<std::endl;
    }
    TTF_Quit();
    std::cout << "TextManager singleton destroyed." << std::endl;
}

TTF_Font* TextManager::get_font(std::string id) {
    return m_fonts[id];
}

SDL_Color TextManager::get_color(std::string id) {
    return m_colors[id];
}

TextObject* TextManager::get_text(std::string id) {
    return m_texts[id];
}

void TextManager::render_all(void) {
    for ( auto text : m_texts) {
        m_texts[text.first]->render();
    }
}

TextObject* TextManager::create(std::string id, std::string text) {
    if (m_texts.count(id) == 1) {
        std::cout << "TextManager already contains text object with id: " << id << std::endl;
    } else {
        m_texts[id] = new TextObject(id, text);
        return m_texts[id];
    }
}

void TextManager::remove(std::string id) {
    if ( m_texts.count(id) == 1) {
        m_texts.erase(id);
    } else {
        std::cout << "TextManager doesn't contains text object with given id: " << std::endl;
    }
}

void TextManager::add_color(std::string id, Uint8 R, Uint8 G, Uint8 B) {
    SDL_Color l_color = {R, G, B};
    if (m_colors.count(id) == 1) {
        std::cout << "TextManager already contains color with id: " << id << std::endl;
    } else {
        m_colors[id] = l_color;
    }
}

void TextManager::remove_color(std::string id) {
    if ( m_colors.count(id) == 1) {
        m_colors.erase(id);
    } else {
        std::cout << "TextManager doesn't contains color with given id: " << std::endl;
    }
}

void TextManager::add_font(std::string id, std::string file, int size) {
    if ( m_fonts.count(id) == 1) {
        std::cout << "TextManager already contains font with given id: " << id << std::endl;
    } else {
        std::string file_path = m_font_folder + file;
        m_fonts[id] = TTF_OpenFont(file_path.c_str(), size);
    }
}

void TextManager::set_default_color(std::string id) {
    if ( m_colors.count(id) == 1) {
        std::cout << "Error while setting default color.TextManager doesn't contains color with given id: " << id << std::endl;
    } else {
        std::transform(id.begin(), id.end(), id.begin(), ::toupper);
        DEFAULT_COLOR = id;
    }
}

void TextManager::set_default_font(std::string id) {
    std::transform(id.begin(), id.end(), id.begin(), ::toupper);
    if (m_fonts.count(id) == 1) {
        DEFAULT_FONT_NAME = id;
    } else {
        std::cout << "Couldn't set default font. There is no font with id: " << id << std::endl;
    }
}
