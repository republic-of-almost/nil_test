#!lua

package.path = '../nil/?.lua;' .. package.path
package.path = './?.lua;' .. package.path
package.path = '../premake_data/?.lua;' .. package.path

require "premake_data"

dofile("../nil/project.lua")
dofile("../premake_data/premake_data.lua")
dofile("project.lua")


-- Solution data? Should this contain the the project names?
solution_data = {

  name = "NilDev",

}

-- Defaults will be based on platform in the future.
-- Currently only supports buildoptions.
project_defaults = {

  buildoptions_macosx = {
    "-std=c++14",
    "-stdlib=libc++",
  },

  buildoptions_windows = {
    "/IGNORE:C4577",
  },

  flags = {
    "EnableSSE2",
    "ExtraWarnings",
    "FloatFast",
    "NoExceptions", -- deprecated
    "NoRTTI", -- deprecated
  },

  defines = {
    "MATH_USE_SIMD",
    "OP_BUFFER_LOG_ERRORS",
    "OP_BUFFER_LOG_INFO",
    "OP_BUFFER_API_OGL",
    "OP_BUFFER_API_OGL_EXTRA_CHECKS",
  },

  defines_windows = {
    "_HAS_EXCEPTIONS=0",
    "_CRT_NO_WARNINGS",
  },

  exceptions = false,
  rtti = false,
}

-- Generates the premake code calls.
make.create_solution(solution_data,
                     project_defaults,
                     engine_test_data,
                     engine_data)
