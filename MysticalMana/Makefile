OBJS	= Application.o AssetManager.o AudioManager.o InputManager.o MysticalMana.o RendererManager.o Window.o
SOURCE	= Application.cpp AssetManager.cpp AudioManager.cpp InputManager.cpp MysticalMana.cpp RendererManager.cpp Window.cpp
HEADER	= Application.h AssetManager.h AudioEntity.h AudioManager.h BaseEntity.h GlfwWindowDestroyer.h InputManager.h RendererManager.h StaticEntity.h UserInputEvents.h Vertex.h Window.h
OUT	= MysticalMana
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -ldl -lX11 -lpthread -lglfw -lassimp -lfmodL -lGenericCodeGen -lglew-static -lglslang -lGraphicsEngineOpenGL -lGraphicsEngineVk -lHLSL -lMachineIndependent -lOGLCompiler -lOSDependent -lSPIRV -lspirv-cross-core -lSPIRV-Tools -lSPIRV-Tools-opt -lDiligentFX -lDiligentTools

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Application.o: Application.cpp
	$(CC) $(FLAGS) Application.cpp -std=c++17

AssetManager.o: AssetManager.cpp
	$(CC) $(FLAGS) AssetManager.cpp -std=c++17

AudioManager.o: AudioManager.cpp
	$(CC) $(FLAGS) AudioManager.cpp -std=c++17

InputManager.o: InputManager.cpp
	$(CC) $(FLAGS) InputManager.cpp -std=c++17

MysticalMana.o: MysticalMana.cpp
	$(CC) $(FLAGS) MysticalMana.cpp -std=c++17

RendererManager.o: RendererManager.cpp
	$(CC) $(FLAGS) RendererManager.cpp -std=c++17

Window.o: Window.cpp
	$(CC) $(FLAGS) Window.cpp -std=c++17


clean:
	rm -f $(OBJS) $(OUT)