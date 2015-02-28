#ifndef OBJECT_H_DEFINED
#define OBJECT_H_DEFINED

// Abstact class implementing base Object interface.
// All etities must derive from this one to ensure base
// method for all objects.
// Usefull in object factories.
// We should be able for all object to:
// set and get position
// set and get dimensions
// ? set and get state flag ?


class Object {
public:
    Object() {};
    virtual int get_width(void) = 0;
    virtual int get_height(void) = 0;
    virtual int get_x_position(void) = 0;
    virtual int get_y_position(void) = 0;
    virtual void set_width(int width) = 0;
    virtual void set_height(int height) = 0;
    virtual void set_x_position(int x) = 0;
    virtual void set_y_position(int y) = 0;
    virtual bool is_active(void) = 0;
    virtual void enable(void) = 0;
    virtual void disable(void) = 0;
    ~Object() {}
protected:
};

#endif