#ifndef BASEOBJECT_H_DEFINED
#define BASEOBJECT_H_DEFINED

#include <string>

#include <SDL2/SDL.h>

#include "abstract/Object.hpp"


enum COLLISION_TYPE {
    NO_COLLISION, NONE, NO = 0,
    TOP_LEFT, LEFT_TOP, TopLeft, LeftTop, TOPLEFT, LEFTTOP = 1,
    TOP_RIGHT, RIGHT_TOP = 2,
    BOTTOM_RIGHT, RIGHT_BOTTOM = 3,
    BOTTOM_LEFT, LEFT_BOTTOM = 4,
    IN, INSIDE = 5,
    OVER, OUT, ON= 6,
    TOP_OVER = 7,
    RIGHT_OVER = 8,
    BOTTOM_OVER = 9,
    LEFT_OVER = 10,
    TOP_IN = 11,
    RIGHT_IN = 12,
    BOTTOM_IN = 13,
    LEFT_IN = 14,
    HORIZONTAL = 15,
    VERTICAL = 16,
    ALL = 17
};

class BaseObject: public Object {
public:
    BaseObject() {};
    BaseObject(
            std::string ID,
            int x,
            int y,
            int width,
            int height,
            bool state);
    BaseObject(std::string ID, SDL_Point* p1, SDL_Point* p2, bool state);
    const std::string get_ID(void) { return m_ID; } // ID should be constant
    virtual SDL_Rect* get_box() { return &m_box; }
    virtual int get_width(void) { return m_box.w; }
    virtual int get_height(void) { return m_box.h; }
    virtual BaseObject& set_width(int width) { m_box.w = width; return *this; }
    virtual BaseObject& set_height(int height) { m_box.h = height; return *this; }
    virtual SDL_Point* get_position();
    virtual BaseObject& set_position(SDL_Point* p1);
    virtual BaseObject& set_size(SDL_Point* p1, SDL_Point* p2);
    virtual BaseObject& set_position(int x, int y);
    virtual BaseObject& set_position(int x, int y, int width, int height);
    virtual int get_x_position(void) { return m_box.x; }
    virtual int get_y_position(void) { return m_box.y; }
    virtual BaseObject& set_x_position(int x);
    virtual BaseObject& set_y_position(int y);
    virtual BaseObject& move_horizontal(int x);
    virtual BaseObject& move_vertical(int x);
    virtual BaseObject& move_left(int x);
    virtual BaseObject& move_right(int x);
    virtual BaseObject& move_up(int x);
    virtual BaseObject& move_bottom(int x);
    virtual bool is_active(void) { return m_state; }
    virtual BaseObject& enable(void) { m_state = true; return *this; }
    virtual BaseObject& disable(void) { m_state = false; return *this; }
    /* check if object is collided with passed object in certain configuration
     * there is 18 type of collision type - see above for enum
     * default parameter for collision type is ALL, so any collision type will return true
     * else false is returned. */
    virtual bool check_boxes_collision(BaseObject& second_object, COLLISION_TYPE type = ALL);
    virtual SDL_Rect check_boxes_intersection(BaseObject& second_box);
    virtual COLLISION_TYPE check_collision_type(BaseObject& second_box);
    virtual void destroy(void);
    ~BaseObject(void) {};
protected:
    std::string m_ID;
    SDL_Rect m_box;
    bool m_state;
};

#endif /* BASEOBJECT_H_DEFINED */