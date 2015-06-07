//
// Created by g3f4 on 07.06.15.
//

#include <sstream>
#include "CollisionBoard.h"

CollisionBoard::CollisionBoard(BaseObject &obj1, BaseObject &obj2) : m_first(obj1), m_second(obj2) {
    TXT.create("collision-type-text", "No collision");
    TXT.create("intersection-text", "Intersection {x: 0, y: 0 , w: 0, h: 0}");
    TXT.get_text("collision-type-text")->set_x_position(10).set_y_position(10);
    TXT.get_text("intersection-text")->set_x_position(10).set_y_position(50);
    std::cout << "Coliision board created." << std::endl;
}

void CollisionBoard::handle_events() {
    SDL_Rect intersection = m_first.check_boxes_intersection(m_second);
    std::stringstream sstm;
    sstm << "Intersection {x: " << intersection.x << ", y: " << intersection.y << " , w: "<< intersection.w<< ", h: "<< intersection.h << "}";
    std::string input = sstm.str();
    TXT.get_text("intersection-text")->set_text(input);
    if (EVT.key_pressed("a")) {
    }
    if (EVT.key_pressed("s")) {
    }

    if (EVT.key_pressing("LEFT")) {
        m_first.move_left(3);
    }
    if (EVT.key_pressing("RIGHT")) {
        m_first.move_right(3);
    }
    if (EVT.key_pressing("UP")) {
        m_first.move_up(3);
    }
    if (EVT.key_pressing("DOWN")) {
        m_first.move_bottom(3);
    }
    switch (m_first.check_collision_type(m_second)) {
        case NO_COLLISION:
            TXT.get_text("collision-type-text")->set_text("No collision");
            break;
        case TOP_LEFT:
            TXT.get_text("collision-type-text")->set_text("Top left corner collided");
            GFX.get("obj2").move_up(1);
            GFX.get("obj2").move_left(1);
            break;
        case TOP_RIGHT:
            TXT.get_text("collision-type-text")->set_text("Top right corner collided");
            GFX.get("obj2").move_up(1);
            GFX.get("obj2").move_right(1);
            break;
        case BOTTOM_RIGHT:
            TXT.get_text("collision-type-text")->set_text("bottom right corner collided");
            GFX.get("obj2").move_up(-1);
            GFX.get("obj2").move_left(-1);
            break;
        case BOTTOM_LEFT:
            TXT.get_text("collision-type-text")->set_text("bottom left corner collieded");
            GFX.get("obj2").move_up(-1);
            GFX.get("obj2").move_left(1);
            break;
        case IN:
            TXT.get_text("collision-type-text")->set_text("The object is inside");
            break;
        case OVER:
            TXT.get_text("collision-type-text")->set_text("The object lay over other object");
            break;
        case TOP_OVER:
            TXT.get_text("collision-type-text")->set_text("Top side whole covered");
            GFX.get("obj2").move_up(1);
            break;
        case RIGHT_OVER:
            TXT.get_text("collision-type-text")->set_text("Right side whole covered");
            GFX.get("obj2").move_right(1);
            break;
        case BOTTOM_OVER:
            TXT.get_text("collision-type-text")->set_text("bottom side whole covered");
            GFX.get("obj2").move_up(-1);
            break;
        case LEFT_OVER:
            TXT.get_text("collision-type-text")->set_text("left side whole covered");
            GFX.get("obj2").move_left(1);
            break;
        case TOP_IN:
            TXT.get_text("collision-type-text")->set_text("top in");
            GFX.get("obj2").move_up(-1);
            break;
        case RIGHT_IN:
            TXT.get_text("collision-type-text")->set_text("right in");
            GFX.get("obj2").move_right(1);
            break;
        case BOTTOM_IN:
            TXT.get_text("collision-type-text")->set_text("bottom in");
            GFX.get("obj2").move_bottom(1);
            break;
        case LEFT_IN:
            TXT.get_text("collision-type-text")->set_text("left in");
            GFX.get("obj2").move_left(1);
            break;
        case HORIZONTAL:
            TXT.get_text("collision-type-text")->set_text("horizontal");
            break;
        case VERTICAL:
            TXT.get_text("collision-type-text")->set_text("vertical");
            break;
        default:
            TXT.get_text("collision-type-text")->set_text("No collision");
            break;
    }
}
