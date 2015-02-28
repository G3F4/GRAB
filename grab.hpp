#ifndef DEFINE_GRAB_HPP
#define DEFINE_GRAB_HPP

#include "src/singletons/Application.hpp"
#include "src/singletons/Events.hpp"
#include "src/singletons/TextureManager.hpp"


Application& app = Application::Instance();
Events& events = Events::Instance();
TextureManager& gfx = TextureManager::Instance();


#endif /* DEFINE_GRAB_HPP */