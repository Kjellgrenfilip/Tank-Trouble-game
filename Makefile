
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
OBJECTS =  $(OBJDIR)/main.o  $(OBJDIR)/Game.o  $(OBJDIR)/Game_State.o  $(OBJDIR)/Menu_State.o  $(OBJDIR)/Pause_State.o  $(OBJDIR)/Game_Map.o  $(OBJDIR)/Tile.o  $(OBJDIR)/Bullet.o $(OBJDIR)/Player.o  $(OBJDIR)/Resource_Manager.o  $(OBJDIR)/Shield.o  $(OBJDIR)/Rocket.o

# Main objetice - created with 'make' or 'make main'.
main: $(OBJECTS) Makefile 
	$(CCC) -I$(IDIR) $(CCFLAGS) -o tank-trouble $(OBJECTS) $(LDFLAGS)

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

$(OBJDIR)/Game_Map.o: $(SRC)/Game_Map.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_Map.cc -o $(OBJDIR)/Game_Map.o

$(OBJDIR)/Tile.o: $(SRC)/Tile.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Tile.cc -o $(OBJDIR)/Tile.o

$(OBJDIR)/Bullet.o: $(SRC)/Bullet.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Bullet.cc -o $(OBJDIR)/Bullet.o

$(OBJDIR)/Player.o: $(SRC)/Player.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Player.cc -o $(OBJDIR)/Player.o

$(OBJDIR)/Resource_Manager.o: $(SRC)/Resource_Manager.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Resource_Manager.cc -o $(OBJDIR)/Resource_Manager.o

$(OBJDIR)/Shield.o: $(SRC)/Shield.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Shield.cc -o $(OBJDIR)/Shield.o

$(OBJDIR)/Rocket.o: $(SRC)/Rocket.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Rocket.cc -o $(OBJDIR)/Rocket.o

dir:
	@mkdir -p $(OBJDIR)

clean:
	rm tank-trouble $(OBJECTS)



