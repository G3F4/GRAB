#include "Application.hpp"

std::unique_ptr<Application> Application::m_instance;
std::once_flag Application::m_once_flag;

Application& Application::Instance() {
    std::call_once(m_once_flag, [] {
        m_instance.reset(new Application);
    });
    return *m_instance.get();
}

Application::Application() {
    m_running = false;
    m_frame_time = 0;
    m_FPS = 30;
    set_FPS(30);
    m_frame_counter = 0;
    m_stopper = 0;
    enable_autoclear();
    enable_autorender();
    std::cout << "Application Manager created!" << std::endl;
}

Application::~Application() {
    std::cout << "Application Manager destroyed!" << std::endl;
}

bool Application::create_window(std::string ID, std::string title, int x, int y, int width, int height, bool state, Uint32 window_flags, Uint32 renderer_flags) {
    if (m_windows.count(ID) > 0) {
        std::cout << "Window with ID: " << ID << " already exits!" << std::endl \
                    << "Please select other ID: ";
        std::string new_ID = "";
        std::cin >> new_ID;
        create_window(new_ID, title, x, y, width, height, state, window_flags, renderer_flags);
    } else {
        m_windows[ID] = new Window(ID, title, x, y, width, height, state, window_flags, renderer_flags);
        // Every time we create first window we set it as default window
        if (m_windows.size() == 1) {
            m_default_window = m_windows[ID];
        }
    }
    return false;
}

Window *Application::get_window(std::string ID) {
    if (m_windows[ID] == nullptr) {
        std::cout << "There is no Window with ID: " << ID << std::endl;
    } else {
        return m_windows[ID];
    }
}

void Application::hide() {
    for (auto win: m_windows) { // c++11 iterating style
        win.second->hide();
    }
}

void Application::show() {
    for (auto win: m_windows) {
        win.second->show();
    }
}

void Application::start() {
    m_running = true;
    m_stopper = SDL_GetTicks();
}

void Application::stop() {
    m_running = false;
}

void Application::pause(Uint32 ms) {
    SDL_Delay(ms);
}

std::map<std::string, Window *> Application::get_windows() {
    return m_windows;
}

void Application::set_default_window(std::string ID) {
    if (m_windows.count(ID) == 0) {
        std::cout << "Window with ID: " << ID << " doesn't exits!" << std::endl \
                    << "Please select other ID: ";
        std::string new_ID = "";
        std::cin >> new_ID;
        set_default_window(new_ID);
    } else {
        m_default_window = m_windows[ID];
    }

}

void Application::clear() {
    for (auto win: m_windows) {
        win.second->clear();
    }
}

void Application::present() {
    for (auto win: m_windows) {
        win.second->present();
    }
}

bool Application::running() {
    main_loop();
    return m_running;
}

void Application::set_FPS(int fps) {
    m_frame_time = (Uint32)1000 / fps;
}

void Application::main_loop() {
    /* If the loop time is less then estimated frame time we need to delay for rest of this difference */
    m_now = SDL_GetTicks();
    if (m_now - m_stopper < m_frame_time) {
        pause(m_frame_time - (m_now - m_stopper));
    }
    m_stopper = m_now;
    m_frame_counter++;
    Events::Instance().handle();
    if (m_autoclear) {
        clear();
    }
    if (m_autorender) {
        TextureManager::Instance().render_all();
        TextManager::Instance().render_all();
    }
    present();
}
