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
      -- Header
      make.get_proj_root() .. "**.hpp",
      make.get_proj_root() .. "**.h",

      -- Source
      make.get_proj_root() .. "**.cpp",
      make.get_proj_root() .. "**.mm",
      make.get_proj_root() .. "**.c",
      make.get_proj_root() .. "**.m",

      -- Doc
      make.get_proj_root() .. "**.md",
      make.get_proj_root() .. "**.txt",
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
