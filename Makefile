
# Folders
SRC = src

# this is the directory I will compile from (i.e. the argument to -I)
IDIR := include

# all object files will be put here
OBJDIR := objdir

# Compiler (g++)
CCC = g++

# Compiling flags
CCFLAGS +=  -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g -I$(SFML_ROOT)/include
#CCFLAGS +=  -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -I$(SFML_ROOT)/include

LDFLAGS += -L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# file which contains the main function
MAINFILE := main.cc

# Object modules
OBJECTS =  $(OBJDIR)/main.o  $(OBJDIR)/Game.o  $(OBJDIR)/Game_State.o  $(OBJDIR)/Menu_State.o  $(OBJDIR)/Pause_State.o $(OBJDIR)/Win_State.o $(OBJDIR)/Game_Map.o  $(OBJDIR)/Tile.o  $(OBJDIR)/Bullet.o $(OBJDIR)/Player.o  $(OBJDIR)/GameMap_Manager.o  $(OBJDIR)/Power_Up.o  $(OBJDIR)/Collision_Handler.o  $(OBJDIR)/Setting_State.o

# Main objetice - created with 'make' or 'make main'.
main: $(OBJECTS) Makefile 
	$(CCC) -I$(IDIR) $(CCFLAGS) -o crazy_tanks $(OBJECTS) $(LDFLAGS)

# Part objectives
$(OBJDIR)/main.o:  $(SRC)/main.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/main.cc -o $(OBJDIR)/main.o

$(OBJDIR)/Game.o: $(SRC)/Game.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game.cc -o $(OBJDIR)/Game.o

$(OBJDIR)/Game_State.o: $(SRC)/Game_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_State.cc -o $(OBJDIR)/Game_State.o

$(OBJDIR)/Menu_State.o: $(SRC)/Menu_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Menu_State.cc -o $(OBJDIR)/Menu_State.o

$(OBJDIR)/Pause_State.o: $(SRC)/Pause_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Pause_State.cc -o $(OBJDIR)/Pause_State.o

$(OBJDIR)/Win_State.o: $(SRC)/Win_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Win_State.cc -o $(OBJDIR)/Win_State.o

$(OBJDIR)/Setting_State.o: $(SRC)/Setting_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Setting_State.cc -o $(OBJDIR)/Setting_State.o

$(OBJDIR)/Game_Map.o: $(SRC)/Game_Map.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_Map.cc -o $(OBJDIR)/Game_Map.o

$(OBJDIR)/Tile.o: $(SRC)/Tile.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Tile.cc -o $(OBJDIR)/Tile.o

$(OBJDIR)/Bullet.o: $(SRC)/Bullet.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Bullet.cc -o $(OBJDIR)/Bullet.o

$(OBJDIR)/Player.o: $(SRC)/Player.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Player.cc -o $(OBJDIR)/Player.o

$(OBJDIR)/GameMap_Manager.o: $(SRC)/GameMap_Manager.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/GameMap_Manager.cc -o $(OBJDIR)/GameMap_Manager.o

$(OBJDIR)/Power_Up.o: $(SRC)/Power_Up.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Power_Up.cc -o $(OBJDIR)/Power_Up.o

$(OBJDIR)/Collision_Handler.o: $(SRC)/Collision_Handler.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Collision_Handler.cc -o $(OBJDIR)/Collision_Handler.o

dir:
	@mkdir -p $(OBJDIR)

clean:
	rm crazy_tanks $(OBJECTS)

run:
	./crazy_tanks

