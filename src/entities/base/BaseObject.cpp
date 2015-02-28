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

void BaseObject::set_position(SDL_Point* p1) {
    if (p1->x >= 0 && p1->y >= 0) {
        m_box.x = p1->x;
        m_box.y = p1->y;
    } else {
        std::cout << "x and y have to be positive numbers!" << std::endl;
    }
}

void BaseObject::set_position(int x, int y) {
    if (x >= 0 && y >= 0) {
        m_box.x = x;
        m_box.y = y;
    } else {
        std::cout << "x and y have to be positive numbers!" << std::endl;
    }
}

void BaseObject::set_x_position(int x) {
    if (x >= 0) {
        m_box.x = x;
    } else {
        std::cout << "x have to be positive number" << std::endl;
    }

}

void BaseObject::set_y_position(int y) {
    if (y >0) {
        m_box.y = y;
    } else {
        std::cout << "y have to be positive number" << std::endl;
    }
}

void BaseObject::destroy(void) {
//    BaseObject::~BaseObject(); #TODO implement working destroy metohod
}

void BaseObject::set_size(SDL_Point *p1, SDL_Point *p2) {
    m_box.x = p1->x;
    m_box.y = p1->y;
    m_box.w = labs(p2->x - p1->x);
    m_box.h = labs(p2->y - p1->y);
}

void BaseObject::set_position(int x, int y, int width, int height) {
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
                std::cout << stringify(LEFT_OVER) << std::endl;
                return 1 == type || type == ALL;
            } else {
                std::cout << "LEFT_OVER" << std::endl;
                return 10 == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                std::cout << "TOP_OVER" << std::endl;
                return 7 == type || type == ALL;
            } else {
                std::cout << "OVER" << std::endl;
                return 6 == type || type == ALL;
            }
        }
    }
    /* first box further to top and closer to left side of the window
    *        _________           ________           _____               _____
    *   _____|___   2|      _____|___  2|       ____| 2 |____       ____| 2 |____
    *   |1      |    |      |1      |   |       |1  |___|   |       | 1 |   |   |
    *   |       |____|      |_______|   |       |           |       |___|   |___|
    *   |_______|                |______|       |___________|           |___|
    *   TOP_RIGHT               RIGHT_OVER      TOP_IN              HORIZONTAL
    * */
    else if (x1 < x2 && y1 > y2 && x1 + w1 > x2 && y1 < y2 + h2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                std::cout << "TOP_IN" << std::endl;
                return 11 == type || type == ALL;
            } else {
                std::cout << "HORIZONTAL" << std::endl;
                return 15 == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                std::cout << "TOP_RIGHT" << std::endl;
                return 2 == type || type == ALL;
            } else {
                std::cout << "RIGHT_OVER" << std::endl;
                return 8 == type || type == ALL;
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
                std::cout << "IN" << std::endl;
                return 5 == type || type == ALL;
            } else {
                std::cout << "BOTTOM_IN" << std::endl;
                return 13 == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                std::cout << "RIGHT_IN" << std::endl;
                return 12 == type || type == ALL;
            } else {
                std::cout << "BOTTOM_RIGHT" << std::endl;
                return 3 == type || type == ALL;
            }
        }
    }
    /* first box closer to top and left side of the window
    *       _________           _________           _________           _____________
    *   ____|       |       ____|       |____   ____|       |____   ____|____       |
    *   |   |   1   |       |   |   1   |   |   |2  |   1   |   |   | 2 |   |   1   |
    *   | 2 |_______|       | 2 |_______|   |   |___|       |___|   |___|___|       |
    *   |_______|           |_______________|       |_______|           |___________|
    *   BOTTOM_LEFT         BOTTOM_OVER         VERTICAL            LEFT_IN
    * */
    else if (x1 > x2 && y1 < y2 && x1 < x2 + w2 && y1 + h1 > y2) {
        if (x1 + w1 > x2 + w2) {
            if (y1 + h1 > y2 + h2) {
                std::cout << "LEFT_IN" << std::endl;
                return 14 == type || type == ALL;
            } else {
                std::cout << "BOTTOM_LEFT" << std::endl;
                return 4 == type || type == ALL;
            }
        } else {
            if (y1 + h1 > y2 + h2) {
                std::cout << "VERTICAL" << std::endl;
                return 16 == type || type == ALL;
            } else {
                std::cout << "BOTTOM_OVER" << std::endl;
                return 9 == type || type == ALL;
            }
        }
    }
    return 0;
}