#ifndef TEXTMANAGER_H_DEFINED
#define TEXTMANAGER_H_DEFINED

#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <map>
#include <memory>
#include <mutex>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application.hpp"
#include "../entities/common/TextObject.hpp"

// TextObject uses TextManager to get font, and color
// Because we are including TextManager class in TextObject header
// we need to deal with circular dependencies

class TextObject;

class TextManager {
public:
    static TextManager& Instance();
    TextManager(void);
    virtual ~TextManager(void);
    TextObject* create(std::string id, std::string text);
    void remove(std::string id);
    void add_font(std::string id, std::string file, int size = 16);
    void set_default_font(std::string id);
    void remove_font(std::string id);
    void add_color(std::string id, Uint8 R, Uint8 G, Uint8 B);
    void set_default_color(std::string id);
    void remove_color(std::string id);
    void render_all(void);
    TTF_Font* get_font(std::string id);
    TTF_Font* get_default_font() { return get_font(DEFAULT_FONT_NAME); };
    SDL_Color get_color(std::string id);
    SDL_Color get_default_color() { return m_colors[DEFAULT_COLOR]; };
    TextObject* get_text(std::string id);
private:

    // TextManager(const TextManager& src) {}; TODO
    // TextManager& operator=(const TextManager& rhs) {}; TODO
    static std::unique_ptr<TextManager> m_instance;
    static std::once_flag m_once_flag;
    std::string m_font_folder;
    std::map<std::string, TTF_Font*> m_fonts;
    std::map<std::string, SDL_Color> m_colors;
    std::map<std::string, TextObject*> m_texts;
    std::string DEFAULT_FONT_FILE = "OpenSans-Regular.ttf";
    std::string DEFAULT_FONT_NAME = "OpenSans-Regular";
    std::string DEFAULT_COLOR = "BLACK";
};

#endif /* TEXTMANAGER_H_DEFINED */