/* Window class implementation */
#include <iostream>

#include "Window.hpp"


Window::Window(std::string ID, std::string title, int x, int y, int width, int height, bool state, Uint32 window_flags, Uint32 renderer_flags):
        BaseObject(ID, x, y, width, height, state),
        m_title(title)
{
    m_window = SDL_CreateWindow(m_title.c_str(), m_box.x, m_box.y, m_box.w, m_box.h, window_flags);
    if ( m_window != NULL) {
        visible = window_flags != SDL_WINDOW_HIDDEN;
        std::cout << "SDL_Window created!" << std::endl;
        m_renderer = SDL_CreateRenderer(m_window, -1, renderer_flags);
        if (m_renderer != NULL) {
            std::cout << "SDL_Renderer created" << std::endl;
            set_color(m_color);
        } else {
            std::cout << "Failed to create SDL_Renderer. Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cout << "Failed to create SDL_Window. Error: " << SDL_GetError() << std::endl;
    }
}

Window& Window::set_title(std::string title) {
    m_title = title;
    SDL_SetWindowTitle(m_window, m_title.c_str());
    return *this;
}

SDL_Renderer *Window::get_renderer() {
    if (m_renderer != NULL) {
        return m_renderer;
    } else {
        std::cout << "Renderer undefined. Returing NULL" << std::endl;
        return NULL;
    }
}

SDL_Window *Window::get_window() {
    return m_window;
}

Window& Window::set_color(SDL_Color color) {
    m_color = color;
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    return *this;
}

SDL_Color Window::get_color() {
    return m_color;
}

Window& Window::clear() {
    SDL_RenderClear(m_renderer);
    return *this;
}

Window& Window::present() {
    SDL_RenderPresent(m_renderer);
    return *this;
}

Window& Window::minimalize() {
    SDL_MinimizeWindow(m_window);
    return *this;
}

Window& Window::maximalize() {
    SDL_MaximizeWindow(m_window);
    return *this;
}

Window& Window::hide() {
    visible = false;
    SDL_HideWindow(m_window);
    return *this;
}

Window& Window::show() {
    visible = true;
    SDL_ShowWindow(m_window);
    return *this;
}

Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

Window& Window::set_x_position(int x) {
    BaseObject::set_x_position(x);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
    return *this;
}

Window& Window::set_y_position(int y) {
    BaseObject::set_y_position(y);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
    return *this;
}

Window& Window::set_position(SDL_Point *p1) {
    BaseObject::set_position(p1);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
    return *this;
}

Window& Window::set_size(SDL_Point *p1, SDL_Point *p2) {
    BaseObject::set_size(p1, p2);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
    return *this;
}

Window& Window::set_position(int x, int y) {
    BaseObject::set_position(x, y);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
    return *this;
}

Window& Window::set_position(int x, int y, int width, int height) {
    BaseObject::set_position(x, y, width, height);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
    return *this;
}

Window& Window::set_width(int width) {
    BaseObject::set_width(width);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
    return *this;
}

Window& Window::set_height(int height) {
    BaseObject::set_height(height);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
    return *this;
}
