#ifndef TEXTOBJECT_HPP_DEFINE
#define TEXTOBJECT_HPP_DEFINE

#include <algorithm>
#include <SDL2/SDL_ttf.h>
#include "../common/Texture.hpp"
#include "../../singletons/TextManager.hpp"


class TextObject: public Texture {
public:
    TextObject(std::string ID,
               std::string text,
               int x = 0,
               int y = 0,
               std::string font = "",
               SDL_Color color = {0, 0, 0},
               std::string window_ID = "default");
    void set_text(std::string text);
    std::string get_text() { return m_text; };
    void set_font(std::string ID);
    TTF_Font* get_font(void) { return m_font; }
    SDL_Color& get_color(void) { return m_color; }
    void set_color(std::string ID);
    void set_color(SDL_Color color= {0, 0, 0});
    void set_color(Uint8 R = 0, Uint8 G = 0, Uint8 B = 0);
    TextObject& set_size(int size);
    int length() { return (int) m_text.length(); } // casting to int because .length() is returning unsigned long
    void empty() { m_text = ""; }
    void capitalize() { std::transform(m_text.begin(), m_text.end(),m_text.begin(), ::toupper); }
    void decapitalize() { std::transform(m_text.begin(), m_text.end(),m_text.begin(), ::tolower); }
    bool create();
    std::string get_font_name() { return m_font_name; }

protected:
    ~TextObject() {};

private:
    std::string m_text = "";
    TTF_Font* m_font = nullptr;
    std::string m_font_name = "default";
    SDL_Color m_color = {0,0,0};
    int m_size = 10;
};

#endif /* TEXTOBJECT_HPP_DEFINE */