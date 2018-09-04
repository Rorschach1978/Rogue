#OBJS specifies which files to compile as part of the project
OBJS = Rogue.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I./SDL2-2.0.8/x86_64-w64-mingw32/include/SDL2 -I./SDL2_ttf-2.0.14/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L./SDL2-2.0.8/x86_64-w64-mingw32/lib -L./SDL2_ttf-2.0.14/lib/x64

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Rogue

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) -g $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run :
	./$(OBJ_NAME)

