#define versions and standards
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#define the project name
project(MysticalMana VERSION 1.0)

#locate headers, sources, and libraries
find_library(DL dl REQUIRED)
find_library(EX11 X11 REQUIRED)
find_library(PTHREAD pthread REQUIRED)
find_library(GLFW glfw REQUIRED)
find_library(ASSIMP assimp REQUIRED)
find_library(FMOD fmodL REQUIRED)
find_library(GENERICCODEGEN GenericCodeGen REQUIRED)
find_library(GLEWSTATIC glew-static REQUIRED)
find_library(GLSLLANG glslang REQUIRED)
find_library(GRAPHICSENGINEOPENGL GraphicsEngineOpenGL REQUIRED)
find_library(GRAPHICSENGINEVK GraphicsEngineVk REQUIRED)
find_library(EHLSL HLSL REQUIRED)
find_library(MACHINEINDEPENDENT MachineIndependent REQUIRED)
find_library(OGLCOMPILER OGLCompiler REQUIRED)
find_library(OSDEPENDENT OSDependent REQUIRED)
find_library(ESPIRV SPIRV REQUIRED)
find_library(SPIRVCROSSCORE spirv-cross-core REQUIRED)
find_library(SPIRVTOOLS SPIRV-Tools REQUIRED)
find_library(SPIRVTOOLSOPT SPIRV-Tools-opt REQUIRED)
find_library(DILIGENTFX DiligentFX REQUIRED)
find_library(DILIGENTTOOLS DiligentTools REQUIRED)

#compile
file(GLOB_RECURSE SRC_FILES MysticalMana/*.cpp)
add_executable(MysticalMana ${SRC_FILES})
target_include_directories(MysticalMana PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MysticalMana)
target_link_libraries(MysticalMana PUBLIC ${DL} ${EX11} ${PTHREAD} ${GLFW} ${ASSIMP} ${FMOD} ${GENERICCODEGEN} ${GLEWSTATIC} ${GLSLLANG} ${GRAPHICSENGINEOPENGL} ${GRAPHICSENGINEVK} ${EHLSL} ${MACHINEINDEPENDENT} ${OGLCOMPILER} ${OSDEPENDENT} ${ESPIRV} ${SPIRVCROSSCORE} ${SPIRVTOOLS} ${SPIRVTOOLSOPT} ${DILIGENTFX} ${DILIGENTTOOLS})