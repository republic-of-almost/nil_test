#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/data/data.hpp>

#include <external/GL/gl3w.h>

#define SDL_ASPECT_IMPL
#include <sdl_aspect.hpp>

#define IMGUI_ASPECT_IMPL
#include <imgui_aspect.hpp>

#define RENDERER_ASPECT_IMPL
#include <renderer_aspect.hpp>


#define ROV_GL_IMPL
#include <external/rov/rov.hpp>

#include <assert.h>

int
main()
{
  Nil::Engine nil_engine;
  
  Nil_ext::SDL_Aspect sdl_aspect;
  nil_engine.add_aspect(&sdl_aspect);
  
  Nil_ext::ImGUI_Aspect imgui_aspect;
  nil_engine.add_aspect(&imgui_aspect);
  
  Nil_ext::GL_Aspect gl_aspect;
  nil_engine.add_aspect(&gl_aspect);
  
  Nil::Node context;
  {
    context.set_name("Ctx");
    
    Nil::Data::Window window{};
    window.width = 0;
    window.height = 0;
    window.fullscreen = false;
    
    Nil::Data::set(context, window);
  }
  
  Nil::Node ground;
  {
    ground.set_name("Ground");
    
    Nil::Data::Material mat{};
    
    Nil::Data::set(ground, mat);
  }
  
  Nil::Node camera;
  {
    camera.set_name("Camera");
    
    Nil::Data::Camera cam{};
    cam.width = 1200;
    cam.height = 720;
    cam.fov = 0.4f;
    cam.near_plane = 0.1f;
    cam.far_plane = 100.f;
    cam.type = Nil::Data::Camera::PERSPECTIVE;
    cam.clear_color_buffer = true;
    cam.clear_depth_buffer = true;
    
    Nil::Data::set(camera, cam);
  }
  
  
  while(nil_engine.run())
  {

  }
  
  
  return 0;
}
