#define versions and standards
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#define the project name
project(MysticalMana VERSION 1.0)

#Add dependency directories
add_subdirectory("DiligentCore")
add_subdirectory("DiligentTools")

#locate UNIX and WIN specific libs
if(UNIX)
elseif(WIN32)   
endif()

#Add headers, sources, and assets
file(GLOB_RECURSE SRC_FILES MysticalMana/*.cpp)
file(GLOB_RECURSE INCL_FILES MysticalMana/*.h)
file(COPY MysticalMana/vertex.hlsl DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY MysticalMana/fragment.hlsl DESTINATION ${CMAKE_BINARY_DIR}/Debug)

#define the application executable
add_executable(MysticalMana ${SRC_FILES} ${INCL_FILES})

#define include directory
target_compile_options(MysticalMana PRIVATE -DUNICODE -DENGINE_DLL)
target_include_directories(MysticalMana 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MysticalMana
    PRIVATE
        "/home/rr-linux/Code/Build/DiligentEngine/DiligentCore"
        "/home/rr-linux/Code/Build/DiligentEngine/DiligentTools"
)

#link libraries
if(UNIX)
    target_link_libraries(MysticalMana
        PRIVATE
            Diligent-GraphicsEngineVk-shared
            Diligent-TextureLoader
            SDL2
            SDL2main
            SDL2_mixer
            glfw3
            assimp
            xcb
            GL
            X11
            pthread
            dl
    )
elseif(WIN32)
endif()
