#ifndef DEFINE_GRAB_HPP
#define DEFINE_GRAB_HPP

#include "src/singletons/Application.hpp"
#include "src/singletons/Events.hpp"
#include "src/singletons/TextureManager.hpp"
#include "src/singletons/TextManager.hpp"


Application& APP = Application::Instance();
Events& EVT = Events::Instance();
TextureManager& GFX = TextureManager::Instance();
TextManager& TXT = TextManager::Instance();


#endif /* DEFINE_GRAB_HPP */