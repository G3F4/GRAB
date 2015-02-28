/* Window class implementation */
#include <iostream>

#include "Window.hpp"


Window::Window(std::string ID, int x, int y, int width, int height, bool state, Uint32 window_flags, Uint32 renderer_flags):
        BaseObject(ID, x, y, width, height, state)
{
    m_window = SDL_CreateWindow(m_ID.c_str(), m_box.x, m_box.y, m_box.w, m_box.h, window_flags);
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

void Window::set_title(std::string title) {
    SDL_SetWindowTitle(m_window, title.c_str());
}

std::string Window::get_title() {
    return SDL_GetWindowTitle(m_window);
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

void Window::set_color(SDL_Color color) {
    m_color = color;
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
}

SDL_Color Window::get_color() {
    return m_color;
}

void Window::clear() {
    SDL_RenderClear(m_renderer);
}

void Window::present() {
    SDL_RenderPresent(m_renderer);
}

void Window::minimalize() {
    SDL_MinimizeWindow(m_window);
}

void Window::maximalize() {
    SDL_MaximizeWindow(m_window);
}

void Window::hide() {
    visible = false;
    SDL_HideWindow(m_window);
}

void Window::show() {
    visible = true;
    SDL_ShowWindow(m_window);
}

Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::set_x_position(int x) {
    BaseObject::set_x_position(x);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
}

void Window::set_y_position(int y) {
    BaseObject::set_y_position(y);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
}

void Window::set_position(SDL_Point *p1) {
    BaseObject::set_position(p1);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
}

void Window::set_size(SDL_Point *p1, SDL_Point *p2) {
    BaseObject::set_size(p1, p2);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
}

void Window::set_position(int x, int y) {
    BaseObject::set_position(x, y);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
}

void Window::set_position(int x, int y, int width, int height) {
    BaseObject::set_position(x, y, width, height);
    SDL_SetWindowPosition(m_window, m_box.x, m_box.y);
}

void Window::set_width(int width) {
    BaseObject::set_width(width);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
}

void Window::set_height(int height) {
    BaseObject::set_height(height);
    SDL_SetWindowSize(m_window, m_box.w, m_box.h);
}
