#!lua

engine_test_data = {

  name     = "NilTest",
  kind     = "ConsoleApp",
  language = "C++",
  location = make.get_proj_root(),

  src_files = {
    make.get_proj_root() .. "src/**.hpp",
    make.get_proj_root() .. "src/**.cpp",
    make.get_proj_root() .. "src/**.mm",
    make.get_proj_root() .. "src/**.h",
    make.get_proj_root() .. "src/**.c",
    make.get_proj_root() .. "src/**.m",
    make.get_proj_root() .. "src/**.md",

    make.get_proj_root() .. "include/**.hpp",
    make.get_proj_root() .. "include/**.cpp",
    make.get_proj_root() .. "include/**.mm",
    make.get_proj_root() .. "include/**.h",
    make.get_proj_root() .. "include/**.c",
    make.get_proj_root() .. "include/**.m",
    make.get_proj_root() .. "include/**.md",

    make.get_proj_root() .. "../nil_aspects/**.hpp",
    make.get_proj_root() .. "../nil_aspects/**.cpp",
    make.get_proj_root() .. "../nil_aspects/**.mm",
    make.get_proj_root() .. "../nil_aspects/**.h",
    make.get_proj_root() .. "../nil_aspects/**.c",
    make.get_proj_root() .. "../nil_aspects/**.m",
    make.get_proj_root() .. "../nil_aspects/**.md",
  },

  asset_dir = "assets/",

  lib_dirs_macosx = {
    "/usr/local/lib/",
  },

  linkoptions_macosx = {
  },

  inc_dirs_macosx = {
    "/usr/local/include",
  },

  project_dependencies = { -- This should pick up the links
    "Nil",
  },

  inc_dirs = {
    make.get_proj_root() .. "include/",
    make.get_proj_root() .. "src/",
    make.get_proj_root() .. "src/external/",
    make.get_proj_root() .. "src/external/math/",
    make.get_proj_root() .. "src/external/utilities/",
    make.get_proj_root() .. "../nil_aspects/",
    make.get_proj_root() .. "../nil_aspects/external/",
  },
}
