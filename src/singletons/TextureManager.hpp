#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <memory>
#include <mutex>
#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#include "Application.hpp"

#include "../entities/common/Texture.hpp"
#include "../entities/Sprite.hpp"

#include "../utils/comparator.hpp"


class Sprite;

class TextureManager {
public:
    static TextureManager& Instance();
    TextureManager();
    ~TextureManager();
    void render_window(std::string ID);
    void render_all();
    Sprite* get_texture(std::string ID);
    std::map<std::string, Sprite*> get_textures(void) { return m_textures; }
    Sprite& load(std::string ID, std::string file, int x = 0, int y = 0, int width = 0, int height = 0, std::string window_ID = "default", bool state = true);
    bool destroy(std::string ID);
    std::string get_folder() { return m_folder; }
    void set_folder(std::string folder) { m_folder = folder; }
    Sprite& get(std::string ID);
protected:

private:
    std::string m_folder;
    std::map<std::string, Sprite*> m_textures;
    static std::unique_ptr<TextureManager> m_instance;
    static std::once_flag m_once_flag;
};

#endif