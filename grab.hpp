#ifndef DEFINE_GRAB_HPP
#define DEFINE_GRAB_HPP

#include "src/singletons/Application.hpp"
#include "src/singletons/Events.hpp"
#include "src/singletons/TextureManager.hpp"
#include "src/singletons/TextManager.hpp"


static Application& APP = Application::Instance();
static Events& EVT = Events::Instance();
static TextureManager& GFX = TextureManager::Instance();
static TextManager& TXT = TextManager::Instance();


#endif /* DEFINE_GRAB_HPP */