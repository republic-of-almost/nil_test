#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/data/data.hpp>

#include <assets/cube_mesh.hpp>

#include <external/GL/gl3w.h>

#define IMGUI_DEVELOPER_SUPPORT
#define IMGIZMO_DEVELOPER_SUPPORT

#define SDL_ASPECT_IMPL
#include <sdl_aspect.hpp>

#define IMGUI_ASPECT_IMPL
#include <imgui_aspect.hpp>

#define RENDERER_ASPECT_IMPL
#include <renderer_aspect.hpp>


#include <assert.h>

int
main()
{
  Nil::Engine nil_engine;
  
  Nil_ext::SDL_Aspect::Data sdl;
  {
    Nil::Aspect sdl_aspect;
    sdl_aspect.start_up_fn    = Nil_ext::SDL_Aspect::start_up;
    sdl_aspect.events_fn      = Nil_ext::SDL_Aspect::events;
    sdl_aspect.early_think_fn = Nil_ext::SDL_Aspect::early_think;
    sdl_aspect.late_think_fn  = Nil_ext::SDL_Aspect::late_think;
    sdl_aspect.user_data      = (uintptr_t)&sdl;
    
    nil_engine.add_aspect(sdl_aspect);
  }
  
  Nil_ext::ImGui_Aspect::Data imgui;
  {
    Nil::Aspect imgui_aspect;
  
    imgui_aspect.start_up_fn = Nil_ext::ImGui_Aspect::start_up;
    imgui_aspect.events_fn   = Nil_ext::ImGui_Aspect::events;
    imgui_aspect.think_fn    = Nil_ext::ImGui_Aspect::think;
    imgui_aspect.user_data   = (uintptr_t)&imgui;
    
    nil_engine.add_aspect(imgui_aspect);
  }
  
  Nil_ext::ROV_Aspect::Data rov;
  {
    Nil::Aspect rov_aspect;
    
    rov_aspect.start_up_fn    = Nil_ext::ROV_Aspect::start_up;
    rov_aspect.events_fn      = Nil_ext::ROV_Aspect::events;
    rov_aspect.early_think_fn = Nil_ext::ROV_Aspect::early_think;
    rov_aspect.think_fn       = Nil_ext::ROV_Aspect::think;
    rov_aspect.user_data      = (uintptr_t)&rov;
    
    nil_engine.add_aspect(rov_aspect);
  }
  
  Nil::Node context;
  {
    context.set_name("Ctx");
    
    Nil::Data::Window window{};
    window.width = 0;
    window.height = 0;
    window.fullscreen = false;
    const char title[] = "Nil Test";
    memcpy(window.title, title, sizeof(title));
    
    Nil::Data::set(context, window);
  }
  
  Nil::Node ground;
  {
    ground.set_name("Ground");
    
    Nil::Data::Material mat{};
    Nil::Data::set(ground, mat);
    
    Nil::Data::Mesh_resource mesh{};
    
    mesh.position_vec3 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_positions));
    memcpy(mesh.position_vec3, Nil_ext::Mesh::cube_positions, sizeof(Nil_ext::Mesh::cube_positions));
    
    mesh.normal_vec3 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_normals));
    memcpy(mesh.normal_vec3, Nil_ext::Mesh::cube_normals, sizeof(Nil_ext::Mesh::cube_normals));
    
    mesh.texture_coords_vec2 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_texture_coords));
    memcpy(mesh.texture_coords_vec2, Nil_ext::Mesh::cube_texture_coords, sizeof(Nil_ext::Mesh::cube_texture_coords));
    
    mesh.count = 36;
    
    Nil::Data::set(ground, mesh);
    
    Nil::Data::Transform trans{};
    constexpr float zero[] = {0,0,0,0};
    memcpy(trans.position, zero, sizeof(trans.position));
    
    constexpr float one[] = {1,1,1,1};
    memcpy(trans.scale, one, sizeof(trans.scale));
    
    Nil::Data::set(ground, trans);
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
