SRC:= $(wildcard SDLRPG/*.cpp)
OBJ:= $(SRC:%.cpp=%.o)
SF := -std=c++14 -Wall -g
SF += -I/usr/local/include/SDL2 -I./SDLRPG -L/usr/local/lib
LF := -Wl,-rpath,/usr/local/lib -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lSDL2 -g

.PHONY: pbuild build

pbuild:
	@make --silent -j8 build

build: $(OBJ)
	@echo "---- Linking ----"
	@g++ $^ $(LF) -obuild

%.o: %.cpp
	@echo "---- Building $@ ----"
	@g++ $(SF) -c $< -o $@

%.o: %.cpp %.h
	@echo "---- Building $@ ----"
	@g++ $(SF) -c $< -o $@

run: pbuild
	@cd SDLRPG ; ../build

clean:
	@rm $(shell find . -name "*.o")