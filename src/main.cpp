#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/data/data.hpp>

#include <assets/cube_mesh.hpp>


#define IMGUI_DEVELOPER_SUPPORT
#define IMGIZMO_DEVELOPER_SUPPORT

#define SDL_ASPECT_IMPL
#include <sdl_aspect.hpp>

#define IMGUI_ASPECT_IMPL
#include <imgui_aspect.hpp>

#define RENDERER_ASPECT_IMPL
#include <renderer_aspect.hpp>

#define LOGIC_ASPECT_IMPL
#include <logic_aspect.hpp>

#include <assert.h>
#include <stddef.h>


void
logic_foo()
{
  printf("Yo\n");
}


int
main()
{
  Nil::Engine nil_engine;
  
  /*
    Create the aspects that make up this engine.
  */
  
  /*
    SDL Aspect
    --
    Handles window/input and GL init.
  */
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
  
  /*
    ImGui Aspect
    --
    Debugging UI
  */
  Nil_ext::ImGui_Aspect::Data imgui;
  {
    Nil::Aspect imgui_aspect;
  
    imgui_aspect.start_up_fn = Nil_ext::ImGui_Aspect::start_up;
    imgui_aspect.events_fn   = Nil_ext::ImGui_Aspect::events;
    imgui_aspect.think_fn    = Nil_ext::ImGui_Aspect::think;
    imgui_aspect.user_data   = (uintptr_t)&imgui;
    
    nil_engine.add_aspect(imgui_aspect);
  }
  
  /*
    ROV Aspect
    --
    Renderer
  */
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
  
  /*
    Logic Aspect
  */
  Nil_ext::Logic_aspect::Data logic;
  {
    Nil::Aspect logic_aspect;
    
    logic_aspect.start_up_fn    = Nil_ext::Logic_aspect::start_up;
    logic_aspect.events_fn      = Nil_ext::Logic_aspect::events;
    logic_aspect.early_think_fn = Nil_ext::Logic_aspect::early_think;
    logic_aspect.think_fn       = Nil_ext::Logic_aspect::think;
    logic_aspect.user_data      = (uintptr_t)&logic;
    
    nil_engine.add_aspect(logic_aspect);
  }
  
  /*
    Create Nodes
  */
  Nil::Node context;
  {
    context.set_name("Ctx");
    
    // Window
    {
      Nil::Data::Window window{};
      window.width       = 0; // SDL Aspect will auto choose resolution.
      window.height      = 0; // SDL Aspect will auto choose resolution.
      window.fullscreen  = false;
      const char title[] = "Nil Test";
      memcpy(window.title, title, sizeof(title));
      Nil::Data::set(context, window);
    }
  }
  
  Nil::Node ground;
  {
    ground.set_name("Ground");
    
    // Material
    {
      Nil::Data::Material mat{};
      Nil::Data::set(ground, mat);
    }
    
    // Mesh Resource
    {
      Nil::Data::Mesh_resource mesh{};
      
      mesh.position_vec3 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_positions));
      memcpy(mesh.position_vec3, Nil_ext::Mesh::cube_positions, sizeof(Nil_ext::Mesh::cube_positions));
      
      mesh.normal_vec3 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_normals));
      memcpy(mesh.normal_vec3, Nil_ext::Mesh::cube_normals, sizeof(Nil_ext::Mesh::cube_normals));
      
      mesh.texture_coords_vec2 = (float*)malloc(sizeof(Nil_ext::Mesh::cube_texture_coords));
      memcpy(mesh.texture_coords_vec2, Nil_ext::Mesh::cube_texture_coords, sizeof(Nil_ext::Mesh::cube_texture_coords));
      
      mesh.count = 36;
      
      Nil::Data::set(ground, mesh);
    }
    
    // Transform
    {
      Nil::Data::Transform trans{};
      constexpr float zero[] = {0,0,0,0};
      memcpy(trans.position, zero, sizeof(trans.position));
      
      constexpr float one[] = {1,1,1,1};
      memcpy(trans.scale, one, sizeof(trans.scale));
      
      Nil::Data::set(ground, trans);
    }
  }
  
  struct Orbit_point : public Nil_ext::Logic
  {
    Nil::Node camera;
    
    void
    on_start() override
    {
    }
    
    void
    on_think(const float dt) override
    {
      static float time = 0;
      time += dt * 0.05f;
    
      Nil::Data::Transform trans;
      Nil::Data::get(camera, trans);
    
      constexpr float radius = 10.f;
      
      const float x = math::cos(time) * radius;
      const float y = math::sin(time) * radius;
      trans.position[0] = x;
      trans.position[2] = y;
      
      const math::quat rot = math::quat_normalize(math::quat_init_with_axis_angle(0, 1, 0, time + math::quart_tau()));
      
      trans.rotation[0] = rot.data[0];
      trans.rotation[1] = rot.data[1];
      trans.rotation[2] = rot.data[2];
      trans.rotation[3] = rot.data[3];
      
      Nil::Data::set(camera, trans);
    }
    
  } cam_orbit;
  
  {
    cam_orbit.camera.set_name("Camera");
    
    // Set Camera Data
    {
      Nil::Data::Camera cam{};
      cam.width              = 1.f;
      cam.height             = 1.f;
      cam.fov                = 0.4f;
      cam.near_plane         = 0.1f;
      cam.far_plane          = 100.f;
      cam.type               = Nil::Data::Camera::PERSPECTIVE;
      cam.clear_color_buffer = true;
      cam.clear_depth_buffer = true;
      Nil::Data::set(cam_orbit.camera, cam);
    }
    
    // Set Transform Data
    {
      Nil::Data::Transform trans{};
      trans.position[0] = +0.f;
      trans.position[1] = +1.f;
      trans.position[2] = -10.f;
      Nil::Data::set(cam_orbit.camera, trans);
    }
    
    // Logic
    {
      Nil::Data::Logic log{};
      log.logic_id = 1;
      log.aux_01 = (uintptr_t)&cam_orbit;
      Nil::Data::set(cam_orbit.camera, log);
    }
  }
  
  
  while(nil_engine.run())
  {
  }
  
  
  return 0;
}
