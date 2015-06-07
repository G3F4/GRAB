//
// Created by g3f4 on 07.06.15.
//

#ifndef GRAB_COLLISIONBOARD_H
#define GRAB_COLLISIONBOARD_H

#include "../grab.hpp"


class CollisionBoard {
public:
    CollisionBoard(BaseObject& obj1, BaseObject& obj2);
    void handle_events();

    BaseObject& m_first;
    BaseObject& m_second;
};


#endif //GRAB_COLLISIONBOARD_H
