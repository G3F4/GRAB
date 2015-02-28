#ifndef EVENTS_H_DEFINED
#define EVENTS_H_DEFINED

#include <SDL2/SDL.h>
#include <iostream>
#include <typeinfo>
#include <map>
#include <memory>
#include <mutex>

#include "Application.hpp"

class Events {
public:
	static Events& Instance(void);
	void handle(void);
	bool key_pressed(std::string key);
	bool mouse_clicked(std::string button = "left");
	bool mouse_released(void);
	virtual ~Events(void);
    Events();
private:
	void reset_mouse_state(void);
	void reset_key_state(void);
	// Events(const Events& src) {};
	// Events& operator=(const Events& rhs) {};
	SDL_Event m_event;
	static std::unique_ptr<Events> m_instance;
	static std::once_flag m_once_flag;
	const Uint8* m_keys_states;
	Uint32 m_mouse_buttons_states;
	bool m_mouse_state[4] = { false };
	std::map<std::string, bool>m_keyboard_state;
};

#endif /* EVENTS_H_DEFINED */