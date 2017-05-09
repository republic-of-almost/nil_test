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
    
        const float positions[]
      {
      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      };

      const float normals[] {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
      };


      const float texture_coords[] {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
      };
    
    
    Nil::Data::Material mat{};
    
    Nil::Data::set(ground, mat);
    
    Nil::Data::Mesh_resource mesh{};
    
    mesh.position_vec3 = (float*)malloc(sizeof(positions));
    memcpy(mesh.position_vec3, positions, sizeof(positions));
    
    mesh.normal_vec3 = (float*)malloc(sizeof(normals));
    memcpy(mesh.normal_vec3, normals, sizeof(normals));
    
    mesh.texture_coords_vec2 = (float*)malloc(sizeof(texture_coords));
    memcpy(mesh.texture_coords_vec2, texture_coords, sizeof(texture_coords));
    
    mesh.count = 36;
    
    Nil::Data::set(ground, mesh);
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
  
  Nil::Node mesh_load;
  {
    mesh_load.set_name("Mesh to load");
    
    Nil::Data::Resource resource{};
    
    resource.type = Nil::Data::Resource_type::MESH;
    resource.data = 0;
    
    Nil::Data::set(mesh_load, resource);
  }
  
  
  while(nil_engine.run())
  {

  }
  
  
  return 0;
}
