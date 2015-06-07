// Application main entry point
#include "../grab.hpp"

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

    TXT.create("collision", "No collision");

    TXT.get_text("collision")->set_x_position(100).set_y_position(100);
    GFX.load("obj1", "no-img.png", 100, 100, 100, 100);
    GFX.load("obj2", "no-img.png", 300, 300, 200, 200).set_alpha(100);
    int i = 100;
    bool chuj = false;
    int j = GFX.get("obj1").get_x_position();
    while(APP.running()) {

        if (EVT.key_pressed("a")) {
            TXT.get_text("collision")->set_size(i++);
            chuj = true;
        }
        if (EVT.key_pressed("s")) {
            TXT.get_text("collision")->set_size(i--);
            chuj = false;
        }

        if (EVT.key_pressing("LEFT")) {
            j--;
//            GFX.get("obj1").set_x_position(GFX.get("obj1").get_x_position() - 1);
//            GFX.get("obj1").move_left(1);
            GFX.get("obj1").move_horizontal(-1);
        }
        if (EVT.key_pressing("RIGHT")) {
            j++;
//            GFX.get("obj1").set_x_position(GFX.get("obj1").get_x_position() + 1);
//            GFX.get("obj1").move_right(1);
            GFX.get("obj1").move_horizontal(1);
        }
        else if (EVT.key_pressing("UP")) {
//            GFX.get("obj1").set_y_position(GFX.get("obj1").get_y_position() - 10);
//            GFX.get("obj1").move_vertical(1);
            GFX.get("obj1").move_up(1);
        }
        else if (EVT.key_pressing("DOWN")) {
//            GFX.get("obj1").set_y_position(GFX.get("obj1").get_y_position() + 10);
//            GFX.get("obj1").move_vertical(-1);
            GFX.get("obj1").move_up(-1);
        }
        switch (GFX.get("obj1").check_collision_type(GFX.get("obj2"))) {
            case NO_COLLISION:
                TXT.get_text("collision")->set_text("No collision");
                break;
            case TOP_LEFT:
                TXT.get_text("collision")->set_text("Top left corner collided");
                break;
            case TOP_RIGHT:
                TXT.get_text("collision")->set_text("Top right corner collided");
                break;
            case BOTTOM_RIGHT:
                TXT.get_text("collision")->set_text("bottom right corner collided");
                break;
            case BOTTOM_LEFT:
                TXT.get_text("collision")->set_text("bottom left corner collieded");
                break;
            case IN:
                TXT.get_text("collision")->set_text("The object is inside");
                break;
            case OVER:
                TXT.get_text("collision")->set_text("The object lay over other object");
                break;
            case TOP_OVER:
                TXT.get_text("collision")->set_text("Top side whole covered");
                break;
            case RIGHT_OVER:
                TXT.get_text("collision")->set_text("Right side whole covered");
                break;
            case BOTTOM_OVER:
                TXT.get_text("collision")->set_text("bottom side whole covered");
                break;
            case LEFT_OVER:
                TXT.get_text("collision")->set_text("left side whole covered");
                break;
            case TOP_IN:
                TXT.get_text("collision")->set_text("top in");
                break;
            case RIGHT_IN:
                TXT.get_text("collision")->set_text("right in");
                break;
            case BOTTOM_IN:
                TXT.get_text("collision")->set_text("bottom in");
                break;
            case LEFT_IN:
                TXT.get_text("collision")->set_text("left in");
                break;
            case HORIZONTAL:
                TXT.get_text("collision")->set_text("horizontal");
                break;
            case VERTICAL:
                TXT.get_text("collision")->set_text("vertical");
                break;
            default:
                TXT.get_text("collision")->set_text("No collision");
                break;
        }
    }
    return 0;
}
