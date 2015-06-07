#define stringify( name ) # name
#include <iostream>

#include "BaseObject.hpp"

BaseObject::BaseObject(std::string ID, int x, int y, int width, int height, bool state):
m_ID(ID), m_state(state)
{
    m_box.x = x;
    m_box.y = y;
    m_box.w = width;
    m_box.h = height;
}

BaseObject::BaseObject(std::string ID, SDL_Point *p1, SDL_Point *p2, bool state) {
    m_ID = ID;
    BaseObject::set_size(p1, p2);
    m_state = state;
}

SDL_Point* BaseObject::get_position() {
    SDL_Point* tmp = new SDL_Point();
    tmp->x = m_box.x;
    tmp->y = m_box.y;
    return tmp;
}

BaseObject& BaseObject::set_position(SDL_Point* p1) {
    if (p1->x >= 0 && p1->y >= 0) {
        m_box.x = p1->x;
        m_box.y = p1->y;
    } else {
        std::cout << "x and y have to be positive numbers!" << std::endl;
    }
    return *this;
}

BaseObject& BaseObject::set_position(int x, int y) {
    if (x >= 0 && y >= 0) {
        m_box.x = x;
        m_box.y = y;
    } else {
        std::cout << "x and y have to be positive numbers!" << std::endl;
    }
    return *this;
}

BaseObject& BaseObject::set_x_position(int x) {
    if (x >= 0) {
        m_box.x = x;
    } else {
        std::cout << "x have to be positive number" << std::endl;
    }
    return *this;
}

BaseObject& BaseObject::set_y_position(int y) {
    if (y >0) {
        m_box.y = y;
    } else {
        std::cout << "y have to be positive number" << std::endl;
    }
    return *this;
}

void BaseObject::destroy(void) {
//    BaseObject::~BaseObject(); #TODO implement working destroy metohod
}

BaseObject& BaseObject::set_size(SDL_Point *p1, SDL_Point *p2) {
    m_box.x = p1->x;
    m_box.y = p1->y;
    m_box.w = (int)labs(p2->x - p1->x);
    m_box.h = (int)labs(p2->y - p1->y);
    return *this;
}

BaseObject& BaseObject::set_position(int x, int y, int width, int height) {
    if (x > 0 && y >0) {
        m_box.x = x;
        m_box.y = y;
    } else {
        std::cout << "x and y have to be positive numbers! Setting values x and y to 0." << std::endl;
        m_box.x = 0;
        m_box.y = 0;
    }
    m_box.w = width;
    m_box.h = height;
    return *this;
}

bool BaseObject::check_boxes_collision(BaseObject& second_box, COLLISION_TYPE type) {
    BaseObject& first_box = *this;
    int x1 = first_box.get_box()->x;
    int x2 = second_box.get_box()->x;
    int y1 = first_box.get_box()->y;
    int y2 = second_box.get_box()->y;
    int w1 = first_box.get_box()->w;
    int w2 = second_box.get_box()->w;
    int h1 = first_box.get_box()->h;
    int h2 = second_box.get_box()->h;

    /* first box further to top and left side of the window
    *   _________           _________________       _________________       _________
    *   | 2  ___|___        | 2 _________   |       | 2 _________   |       | 2 ____|____
    *   |   |       |       |___|       |___|       |   |   1   |   |       |   |   1   |
    *   |___|   1   |           |   1   |           |   |_______|   |       |   |_______|
    *       |_______|           |_______|           |_______________|       |_______|
    *       TOP_LEFT            TOP_OVER             OVER | ON | OUT        LEFT-OVER
    */
    if (x1 > x2 && y1 > y2 && x1 < x2 + w2 && y1 < y2 + h2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return TOP_LEFT == type || type == ALL;
            } else {
                return LEFT_OVER == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return TOP_OVER == type || type == ALL;
            } else {
                return OVER == type || type == ALL;
            }
        }
    }
    /* first box further to top and closer to left side of the window
    *        _________           ________           _____               _____
    *   _____|___   2|      _____|___  2|       ____| 2 |____       ____| 1 |____
    *   |1      |    |      |1      |   |       |1  |___|   |       | 2 |   |   |
    *   |       |____|      |_______|   |       |           |       |___|   |___|
    *   |_______|                |______|       |___________|           |___|
    *   TOP_RIGHT               RIGHT_OVER      TOP_IN              HORIZONTAL
    * */
    else if (x1 < x2 && y1 > y2 && x1 + w1 > x2 && y1 < y2 + h2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return TOP_IN == type || type == ALL;
            } else {
                return HORIZONTAL == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return TOP_RIGHT == type || type == ALL;
            } else {
                return RIGHT_OVER == type || type == ALL;
            }
        }

    }
    /* first box closer to top and left side of the window
    *   _________           ______________      _____________       ____________
    *   |       |____       | 1 ______   |      |     1     |       |      ____|____
    *   |   1   |   |       |   | 2  |   |      |   _____   |       |  1   |   2   |
    *   |_______| 2 |       |   |____|   |      |___| 2 |___|       |      |_______|
    *       |_______|       |____________|          |___|           |__________|
    *   BOTTOM_RIGHT        IN                  BOTTOM_IN           RIGHT_IN
    * */
    else if (x1 < x2 && y1 < y2 && x1 < x2 + w2 && y1 + h1 > y2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return IN == type || type == ALL;
            } else {
                return BOTTOM_IN == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return RIGHT_IN == type || type == ALL;
            } else if (x1 + w1 > x2){
                return BOTTOM_RIGHT == type || type == ALL;
            }
        }
    }
    /* first box closer to top and left side of the window
    *       _________           _________           _________           _____________
    *   ____|       |       ____|       |____   ____|       |____   ____|____       |
    *   |   |   1   |       |   |   1   |   |   |1  |   2   |   |   | 2 |   |   1   |
    *   | 2 |_______|       | 2 |_______|   |   |___|       |___|   |___|___|       |
    *   |_______|           |_______________|       |_______|           |___________|
    *   BOTTOM_LEFT         BOTTOM_OVER             VERTICAL           LEFT_IN
    * */
    else if (x1 > x2 && y1 < y2 && x1 < x2 + w2 && y1 + h1 > y2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return LEFT_IN == type || type == ALL;
            } else {
                return BOTTOM_LEFT == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                std::cout << "VERTICAL" << std::endl;
                return VERTICAL == type || type == ALL;
            } else {
                return BOTTOM_OVER == type || type == ALL;
            }
        }
    }
    return 0;
}

SDL_Rect BaseObject::check_boxes_intersection(BaseObject &second_box) {
    SDL_Rect intersection = {0, 0, 0, 0};
    int collision_type = check_collision_type(second_box);
    /* We are checking collision type for no collision now to safe space for unneeded variables */
    if (collision_type == NO_COLLISION) {
        return intersection;
    }
    /* We declare pointer to this for better reading and semantics */
    BaseObject& first_box = *this;
    int x1 = first_box.get_box()->x;
    int x2 = second_box.get_box()->x;
    int y1 = first_box.get_box()->y;
    int y2 = second_box.get_box()->y;
    int w1 = first_box.get_box()->w;
    int w2 = second_box.get_box()->w;
    int h1 = first_box.get_box()->h;
    int h2 = second_box.get_box()->h;
    /* first box further to top and left side of the window
    *   _________
    *   | 2  ___|____
    *   |   | I |   |
    *   |___|___|1  |
    *       |_______|
    *       TOP_LEFT
    */
    if (collision_type == TOP_LEFT) {
        intersection.x = x1;
        intersection.y = y1;
        intersection.w = (x2 + w2) - w1;
        intersection.h = (y2 + h2) - h1;
        return intersection;
    }
    /* first box further to top and left side of the window
    *  _________________
    *  | 2 _________   |
    *  |___|___I___|___|
    *      |   1   |
    *      |_______|
    *      TOP_OVER INTERSECTION
    */
    if (collision_type == TOP_OVER) {
        intersection.x = x1;
        intersection.y = y1;
        intersection.w = w1;
        intersection.h = (y2 + h2) - y1;
        return intersection;
    }
    /* first box further to top and left side of the window
    *  _________________
    *  | 2 _________   |
    *  |   |   1   |   |
    *  |   |_______|   |
    *  |_______________|
    *  IN INTERSECTION
    */
    if (collision_type == OVER) {
        intersection.x = x1;
        intersection.y = y1;
        intersection.w = w1;
        intersection.h = h1;
        return intersection;
    }
    /* first box further to top and left side of the window
    *  _________
    *  | 2 ____|____
    *  |   |I  |  1|
    *  |   |___|___|
    *  |_______|
    *  LEFT_OVER INTERSECTION
    */
    if (collision_type == LEFT_OVER) {
        intersection.x = x1;
        intersection.y = y1;
        intersection.w = (x2 + w2) - w1;
        intersection.h = h1;
        return intersection;
    }
    /* first box further to top and closer to left side of the window
    *        _________
    *   _____|___   2|
    *   |1   | I|    |
    *   |    |__|____|
    *   |_______|
    *   TOP_RIGHT
    * */
    if (collision_type == TOP_RIGHT) {
        intersection.x = x2;
        intersection.y = y1;
        intersection.w = (x1 + w1) - x2;
        intersection.h = (y2 + h2) - y1;
        return intersection;
    }
    /* * * * * * * * * * * * * * * * * *
    *       ________
    *  _____|___  2|
    *  |1   | I|   |
    *  |____|__|   |
    *       |______|
    *      RIGHT_OVER
    */
    if (collision_type == RIGHT_OVER) {
        intersection.x = x2;
        intersection.y = y1;
        intersection.w = (x1 + w1) - x2;
        intersection.h = h1;
        return intersection;
    }
    /*
    *      _____
    *  ____|_2_|____
    *  |1  |___|   |
    *  |           |
    *  |___________|
    *  TOP_IN
    */
    if (collision_type == TOP_IN) {
        intersection.x = x2;
        intersection.y = y1;
        intersection.w = w2;
        intersection.h = (y2 + h2) - y1;
        return intersection;
    }
    /*
    *      _____
    *  ____|_2_|____
    *  | 1 | I |   |
    *  |___|___|___|
    *      |___|
    *  VERTICAL
    */
    if (collision_type == VERTICAL) {
        intersection.x = x2;
        intersection.y = y1;
        intersection.w = w2;
        intersection.h = h1;
        return intersection;
    }
    /* * * * * * * * * * * *
    *   _________          *
    *   |1  ____|____      *
    *   |   | I |   |      *
    *   |___|___| 2 |      *
    *       |_______|      *
    *                      *
    * * * BOTTOM_RIGHT * * */
    if (collision_type == BOTTOM_RIGHT) {
        intersection.x = x2;
        intersection.y = y2;
        intersection.w = (x1 + w1) - x2;
        intersection.h = (y1 + h1) - y2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *    ______________    *
    *    | 1 ______   |    *
    *    |   | 2  |   |    *
    *    |   |____|   |    *
    *    |____________|    *
    *                      *
    * * * * * IN * * * * * */
    if (collision_type == IN) {
        intersection.x = x2;
        intersection.y = y2;
        intersection.w = w2;
        intersection.h = h2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *     _____________    *
    *     |     1     |    *
    *     |   _____   |    *
    *     |___|_2_|___|    *
    *         |___|        *
    *                      *
    * * * * BOTTOM_IN * * */
    if (collision_type == BOTTOM_IN) {
        intersection.x = x2;
        intersection.y = y2;
        intersection.w = w2;
        intersection.h = (y1 + h1) - y2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *   ____________       *
    *   |      ____|____   *
    *   |  1   | I |  2|   *
    *   |      |___|___|   *
    *   |__________|       *
    *                      *
    * * * * RIGHT_IN * * * */
    if (collision_type == RIGHT_IN) {
        intersection.x = x2;
        intersection.y = y2;
        intersection.w = (x1 + w1) - x2;
        intersection.h = h2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *       _________      *
    *   ____|____  1|      *
    *   |   | I |   |      *
    *   | 2 |___|___|      *
    *   |_______|          *
    *                      *
    * * * BOTTOM_LEFT * * */
    if (collision_type == BOTTOM_LEFT) {
        intersection.x = x1;
        intersection.y = y2;
        intersection.w = (x2 + w2) - x1;
        intersection.h = (y1 + h1) - y2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *      _________       *
    *  ____|_____1_|____   *
    *  |   |   I   |   |   *
    *  | 2 |_______|   |   *
    *  |_______________|   *
    *   BOTTOM_OVER        *
    * * * BOTTOM_OVER * * */
    if (collision_type == BOTTOM_OVER) {
        intersection.x = x1;
        intersection.y = y2;
        intersection.w = w1;
        intersection.h = (y1 + h1) - y2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *       _________      *
    *   ____|______1|____  *
    *   |2  |   I   |   |  *
    *   |___|_______|___|  *
    *       |_______|      *
    *                      *
    * * * * VERTICAL * * * */
    if (collision_type == HORIZONTAL) {
        intersection.x = x1;
        intersection.y = y2;
        intersection.w = w1;
        intersection.h = h2;
        return intersection;
    }
    /* * * * * * * * * * * *
    *      _____________   *
    *  ____|____       |   *`
    *  | 2 |   |   1   |   *
    *  |___|___|       |   *
    *      |___________|   *
    *                      *
    * * * * LEFT_IN * * * */
    if (collision_type == LEFT_IN) {
        intersection.x = x1;
        intersection.y = y2;
        intersection.w = (x2 + w2) - x1;
        intersection.h = h2;
        return intersection;
    }
    return intersection;
}

COLLISION_TYPE BaseObject::check_collision_type(BaseObject &second_box) {
    BaseObject& first_box = *this;
    int x1 = first_box.get_box()->x;
    int x2 = second_box.get_box()->x;
    int y1 = first_box.get_box()->y;
    int y2 = second_box.get_box()->y;
    int w1 = first_box.get_box()->w;
    int w2 = second_box.get_box()->w;
    int h1 = first_box.get_box()->h;
    int h2 = second_box.get_box()->h;

    if (x1 > x2 && y1 > y2 && x1 < x2 + w2 && y1 < y2 + h2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return TOP_LEFT;
            } else {
                return LEFT_OVER;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return TOP_OVER;
            } else {
                return OVER;
            }
        }
    }
    else if (x1 < x2 && y1 > y2 && x1 + w1 > x2 && y1 < y2 + h2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return TOP_IN;
            } else {
                return VERTICAL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return TOP_RIGHT;
            } else {
                return RIGHT_OVER;
            }
        }
    }
    else if (x1 < x2 && y1 < y2 && x1 < x2 + w2 && y1 + h1 > y2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return IN;
            } else {
                return BOTTOM_IN;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return RIGHT_IN;
            } else if (x1 + w1 > x2){
                return BOTTOM_RIGHT;
            }
        }
    }
    else if (x1 > x2 && y1 < y2 && x1 < x2 + w2 && y1 + h1 > y2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                return LEFT_IN;
            } else {
                return BOTTOM_LEFT;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                return HORIZONTAL;
            } else {
                return BOTTOM_OVER;
            }
        }
    }
}

BaseObject &BaseObject::move_horizontal(int x) {
    set_x_position(get_x_position() + x);
    return *this;
}

BaseObject &BaseObject::move_vertical(int x) {
    set_y_position(get_y_position() - x);
    return *this;
}

BaseObject &BaseObject::move_left(int x) {
    move_horizontal(-x);
    return *this;
}

BaseObject &BaseObject::move_right(int x) {
    move_horizontal(x);
    return *this;
}

BaseObject &BaseObject::move_up(int x) {
    move_vertical(x);
    return *this;
}

BaseObject &BaseObject::move_bottom(int x) {
    move_vertical(-x);
    return *this;
}
