// Application main entry point
#include "grab.hpp"
#include "demo/CollisionBoard.h"

int main( int argc, char * argv[] )
{
    /*To simplify we can make handles to our singletons or use it with namespace selector like that:
    * Application::Instance().start() */
    APP.start();
    APP.create_window();
    /* This is main loop of the application.
     * Making main loop is simple as making loop which check if application is still running.
     * Inside loop You can put all your code.
     * You can disable automatic clearing and rendering to have more control over loop. */


    GFX.load("obj1", "no-img.png", 100, 100, 100, 100);
    GFX.load("obj2", "no-img.png", 250, 250, 200, 200).set_alpha(100);
    CollisionBoard* board = new CollisionBoard(GFX.get("obj1"), GFX.get("obj2"));
    while(APP.running()) {
        board->handle_events();
    }
    return 0;
}
