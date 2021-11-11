#define versions and standards
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#define the project name
project(MysticalMana VERSION 1.0)

#locate UNIX and WIN specific libs
if(UNIX)
    find_library(DL dl)
    find_library(EX11 X11)
    find_library(PTHREAD pthread)
elseif(WIN32)
    find_library(DILIGENTWIN32 Diligent-Win32Platform PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTSHADERTOOLS Diligent-ShaderTools PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTPRIMITIVES Diligent-Primitives PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTHLSL2GLSL Diligent-HLSL2GLSLConverterLib PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTGRAPHICSENGINE Diligent-GraphicsEngine PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTACCESSORIES Diligent-GraphicsAccessories PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTCOMMON Diligent-Common PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
    find_library(DILIGENTBASICPLATFORM Diligent-BasicPlatform PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)        
endif()

find_library(GLFW glfw3 PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(ASSIMP assimp-vc142-mtd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" assimp REQUIRED)
find_library(FMOD fmodL_vc PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" fmodL REQUIRED)
find_library(GENERICCODEGEN GenericCodeGen GenericCodeGend PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(GLEWSTATIC glew-static PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(GLSLLANG glslang glslangd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(GRAPHICSENGINEOPENGL GraphicsEngineOpenGL Diligent-GraphicsEngineOpenGL-static PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" GraphicsEngineOpenGL REQUIRED)
find_library(GRAPHICSENGINEVK GraphicsEngineVk Diligent-GraphicsEngineVk-static PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED) 
find_library(EHLSL HLSL HLSLd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(MACHINEINDEPENDENT MachineIndependent MachineIndependentd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(OGLCOMPILER OGLCompiler OGLCompilerd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(OSDEPENDENT OSDependent OSDependentd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(ESPIRV SPIRV SPIRVd PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(SPIRVCROSSCORE spirv-cross-core spirv-cross-cored PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(SPIRVTOOLS SPIRV-Tools PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(SPIRVTOOLSOPT SPIRV-Tools-opt PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(DILIGENTFX DiligentFX PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)
find_library(DILIGENTTOOLS DiligentTools Diligent-GraphicsTools PATHS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64" REQUIRED)


#Add headers, sources, and assets
file(GLOB_RECURSE SRC_FILES MysticalMana/*.cpp)
file(GLOB_RECURSE INCL_FILES MysticalMana/*.h)
file(COPY MysticalMana/vertex.hlsl DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY MysticalMana/fragment.hlsl DESTINATION ${CMAKE_BINARY_DIR}/Debug)

add_executable(MysticalMana ${SRC_FILES} ${INCL_FILES})

#define include directory
target_include_directories(MysticalMana PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MysticalMana)

#link libraries
if(UNIX)
    target_link_libraries(MysticalMana PUBLIC ${DL} ${EX11} ${PTHREAD} ${GLFW} ${ASSIMP} ${FMOD} ${GENERICCODEGEN} ${GLEWSTATIC} ${GLSLLANG} ${GRAPHICSENGINEOPENGL} ${GRAPHICSENGINEVK} ${EHLSL} ${MACHINEINDEPENDENT} ${OGLCOMPILER} ${OSDEPENDENT} ${ESPIRV} ${SPIRVCROSSCORE} ${SPIRVTOOLS} ${SPIRVTOOLSOPT} ${DILIGENTFX} ${DILIGENTTOOLS})
elseif(WIN32)
    target_link_libraries(MysticalMana PUBLIC ${DILIGENTWIN32} ${DILIGENTSHADERTOOLS} ${DILIGENTPRIMITIVES} ${DILIGENTHLSL2GLSL} ${DILIGENTGRAPHICSENGINE} ${DILIGENTACCESSORIES} ${DILIGENTCOMMON} ${DILIGENTBASICPLATFORM} ${GLFW} ${ASSIMP} ${FMOD} ${GENERICCODEGEN} ${GLEWSTATIC} ${GLSLLANG} ${GRAPHICSENGINEOPENGL} ${GRAPHICSENGINEVK} ${EHLSL} ${MACHINEINDEPENDENT} ${OGLCOMPILER} ${OSDEPENDENT} ${ESPIRV} ${SPIRVCROSSCORE} ${SPIRVTOOLS} ${SPIRVTOOLSOPT} ${DILIGENTFX} ${DILIGENTTOOLS})
endif()