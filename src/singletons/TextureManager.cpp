/* TextureManager definitions */
#include "TextureManager.hpp"

std::unique_ptr<TextureManager> TextureManager::m_instance;
std::once_flag TextureManager::m_once_flag;

TextureManager::TextureManager() {
    m_folder = "././assets/images/";
	std::cout << "Texture Manager singleton created." << std::endl;
}

TextureManager& TextureManager::Instance() {
    std::call_once(m_once_flag, [] {
        m_instance.reset(new TextureManager);
    });
    return *m_instance.get();
}

TextureManager::~TextureManager() {
    std::cout << "Texture Manager singleton destroyed." << std::endl;
}

void TextureManager::render_all() {
    for ( auto tex: m_textures) {
        tex.second->render();
    }
}

Texture *TextureManager::get_texture(std::string ID) {
    return m_textures[ID];
}

void TextureManager::render_window(std::string ID) {
    for (auto tex: m_textures) {
        if (tex.second->get_window_ID() == ID) {
            tex.second->render();
        }
    }
}

bool TextureManager::load(std::string ID, std::string file, int x, int y, int width, int height, std::string window_ID, bool state) {
    m_textures[ID] = new Texture(ID, m_folder + file, x, y, width, height, window_ID, state);
}

bool TextureManager::destroy(std::string ID) {
    if (m_textures.count(ID) == 0) {
        std::cout << "There is no Texture with given ID: " << ID << "." << std::endl;
        return false;
    } else {
        m_textures[ID]->destroy();
        m_textures.erase(ID);
        return true;
    }
}
