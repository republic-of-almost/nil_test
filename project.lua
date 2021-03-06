#!lua

--[[
  Test Project Description
]]--

table.insert(
  projects,
  {
    name     = "Test",
    kind     = "WindowedApp",
    language = "C++",
    location = make.get_proj_root(),

    src_files = {
      make.add_headers(make.get_proj_root()),
      make.add_src(make.get_proj_root()),
      make.add_doc(make.get_proj_root()),
    },

    -- asset_dir = "assets/",

    lib_dirs_macosx = {
      "/usr/local/lib/",
    },

    linkoptions_macosx = {
    },

    inc_dirs_macosx = {
      "/usr/local/include",
    },

    project_dependencies = {
      "Nil",
      "Utilities",
      "External",
      "ROV",
      "Math",
      "Aspects",
    },

    inc_dirs = {
      make.get_proj_root() .. "include/",
      make.get_proj_root() .. "src/",
      make.get_proj_root() .. "../nil_aspects/",
    },
  }
)
