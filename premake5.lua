-- premake5.lua
workspace "SpriteDocks"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SpriteDocks"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "WalnutApp"