#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/data/window.hpp>

#define SDL_ASPECT_IMPL
#include <sdl_aspect.hpp>

#define IMGUI_ASPECT_IMPL
#include <imgui_aspect.hpp>

#include <assert.h>

int
main()
{
  Nil::Engine nil_engine;
  
  Nil_ext::SDL_Aspect sdl_aspect;
  nil_engine.add_aspect(&sdl_aspect);
  
  Nil_ext::ImGUI_Aspect imgui_aspect;
  nil_engine.add_aspect(&imgui_aspect);
  
  Nil::Node context;
  context.set_name("ctx");
  
  Nil::Node input;
  input.set_name("input");
  input.set_parent(context);
  
  Nil::Node keyboard_mouse;
  keyboard_mouse.set_name("kb-mouse");
  keyboard_mouse.set_parent(input);
  
  
  context.set_name("ctx");
  {
    Nil::Data::Window window{};
    window.width = 0;
    window.height = 0;
    window.fullscreen = false;
    
    Nil::Data::get(context, window);
    
    Nil::Data::set(context, window);
  }
  
  while(nil_engine.run());
  
  
  return 0;
}
