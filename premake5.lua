-- premake5.lua
workspace "MTGStats"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "MTGStats"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "MTGStats"