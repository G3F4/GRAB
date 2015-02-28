#include "Events.hpp"

std::unique_ptr<Events> Events::m_instance;
std::once_flag Events::m_once_flag;

Events& Events::Instance() {
	std::call_once(m_once_flag, [] {
		m_instance.reset(new Events);
	});
	return *m_instance.get();
}

Events::Events(void) {
    std::cout << "Events singelton created." << std::endl;
    m_keys_states = 0;
    m_mouse_buttons_states = 0;
}

Events::~Events(void) {
    std::cout << "Events singleton destroyed." << std::endl;
}

bool Events::key_pressed(std::string key) {
	//check if any key has pressed state
    if (key.empty()) {
        return false;
    } else {
        if (m_keys_states != 0) {
            // check if particular key is pressed
            if (m_keys_states[SDL_GetScancodeFromName(key.c_str())] == 1
                    && m_keyboard_state[key] != true) {
                std::cout << "Key '" << key << "' was pressed." << std::endl;
                m_keyboard_state[key] = true;
                return true;
            } else {
                return false;
            }
        }
    }
}

void Events::reset_key_state(void) {
	// iterating througth m_keyboard_state to check which button released
	// if key state is 0 it means the button was released
	// if so we change the state of proper key in m_keyboard_state to false
	for (auto key : m_keyboard_state) {
		if (m_keys_states[SDL_GetScancodeFromName(key.first.c_str())] == 0
			&& key.second) {
			std::cout << "Key '" << key.first <<  "' was released." << std::endl;
			m_keyboard_state[key.first] = false;
		}
	}
}

bool Events::mouse_clicked(std::string button) {
	if (m_mouse_buttons_states != 0) {
		if (!m_mouse_state[0] && (m_mouse_buttons_states == 1 && (button == "left" || button == "LEFT"))) {
			std::cout << "left mouse button clicked" << std::endl;
			m_mouse_state[0] = true;
			return true;
		} else if (!m_mouse_state[1] && (m_mouse_buttons_states == 4 && (button == "right" || button == "RIGHT"))) {
			std::cout << "right mouse button clicked" << std::endl;
			m_mouse_state[1] = true;
			return true;
		} else if (!m_mouse_state[2] && (m_mouse_buttons_states == 2 && (button == "middle" || button == "MIDDLE"))) {
			std::cout << "middle mouse button clicked" << std::endl;
			m_mouse_state[2] = true;
			return true;
		} else if (!m_mouse_state[3] && (m_mouse_buttons_states == 5 && (button == "both" || button == "BOTH"))) {
			std::cout << "both mouse buttons clicked" << std::endl;
			m_mouse_state[3] = true;
			return true;
		}
	}
	return false;
}

void Events::reset_mouse_state(void) {
	m_mouse_state[0] = m_mouse_state[1] = m_mouse_state[2] = m_mouse_state[3] = false;
}

void Events::handle(void) {
	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
			case SDL_QUIT:
				Application::Instance().stop();
				break;
			case SDL_KEYDOWN:
				// Every time key is pressed we update keys states
				m_keys_states = SDL_GetKeyboardState(NULL);
				break;
			case SDL_KEYUP:
				// Every time key is released we update keys states
				m_keys_states = SDL_GetKeyboardState(NULL);
				reset_key_state();
				break;
			case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
            	// every time any mouse button is clicked we update mouse states
            	m_mouse_buttons_states = SDL_GetMouseState(NULL, NULL);
                break;
            case SDL_MOUSEBUTTONUP:
            	// every time any mouse button is released we update mouse states
            	m_mouse_buttons_states = SDL_GetMouseState(NULL, NULL);
            	reset_mouse_state();
                break;
			default:
				break;
		}
	}
}