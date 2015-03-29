#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED

#include <string>
#include <iostream>
#include <map>

#include <SDL2/SDL.h>

#include "../entities/Window.hpp"
#include "TextureManager.hpp"
#include "TextManager.hpp"
#include "Events.hpp"
#include <memory>
#include <mutex>
#include <iostream>


class Application
{
public:
    static Application& Instance();
    bool create_window(std::string ID = "default",
                       std::string title = "Unnamed window",
                       int x = 0,
                       int y = 0,
                       int width = 800,
                       int height = 600,
                       bool state = true,
                       Uint32 window_flags = SDL_WINDOW_SHOWN,
                       Uint32 renderer_flags = SDL_RENDERER_ACCELERATED );
    Window* get_window(std::string ID);
    std::map<std::string, Window*> get_windows();   // useful for iterating through all windows manager by application
    void hide();                                    // hide all windows
    void show();                                    // show all windows
    void start();                                   // starts application
    void stop();                                    // stops application
    void pause(Uint32 ms);                          // delay application for given amount of miliseconds
    bool running(); /* method controlling game loop. Keeps tracks of frame and more */
    Window* get_default_window() { return m_default_window; } // #TODO add tests for get/set default_window
    void set_default_window(std::string ID); /* set default window referance */
    virtual ~Application(); /* destructor */
    Application(); /* Contructor */
    void clear(); /* clear all windows with window background color */
    void present(); /* present all windows after rendering */
    void set_FPS(int fps); /* set Frame Per Second */
    int get_FPS() { return m_FPS; } /* return Frame Per Second */
    Uint32 get_current_frame() { return m_frame_counter; }  /* return current frame */
    Uint32 get_current_time() { return m_now; } /* return time elapsed till the beggining of the application  */
    void enable_autoclear() { m_autoclear = true; } /* enable automatic windows clearing */
    void disable_autoclear() { m_autoclear = false; } /* disable automatic windows clearing */
    void enable_autorender() { m_autorender = true; } /* enable automatic rendering */
    void disable_autorender() { m_autorender = false; } /* disable automatic rendering */
protected:
private:
    std::map<std::string, Window*> m_windows; /* Map with references to Window object */
    Window* m_default_window; /* Reference to default Window object */
    bool m_autoclear; /* determines if auto clearing is enabled */
    bool m_autorender; /* determines if auto rendering is enabled */
    bool m_running; /* Running flag */
    int m_FPS; /* Frame Per Second */
    Uint32 m_frame_time; /* Estimated frame time */
    Uint32 m_frame_counter; /* Frame counter */
    Uint32 m_stopper; /* Keeps loop time */
    Uint32 m_now; /* Keeps current time in milliseconds from the start of application */
    static std::unique_ptr<Application> m_instance; /* Unique pointer to application instance */
    static std::once_flag m_once_flag; /* once flag used to ensure singleton */
    void main_loop(); /* Main loop of the application */
};

#endif //APPLICATION_H_DEFINED

