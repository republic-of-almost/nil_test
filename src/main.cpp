#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/data/data.hpp>

#include <assets/cube_mesh.hpp>

#include <external/GL/gl3w.h>

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
