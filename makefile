$(VERBOSE).SILENT:

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/
BINNAME = winae
SRCFILES = $(wildcard $(SRCDIR)*.cpp)
OBJFILES = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCFILES))
BINFILE = $(BINDIR)$(BINNAME)
EXOBJECTS = $(wildcard $(OBJDIR)*.o)

help:
	echo "Makefile for the WINAE Encoder"
	echo "by LukaCPP 2018"
	echo "====================================="
	echo "make all     - compile everything"
	echo "make dirs    - create necessary directories"
	echo "make clean   - remove object files"
	echo "make re      - recompile everything"
	echo "               (-> delete objects -> compile all)"
	echo "make install - install compiled binary to /usr/bin"
	echo "               (requires superuser!)"

all : $(OBJFILES)
	echo "Make: Linking binary"
	g++ -o $(BINFILE) $(OBJFILES)
	echo "Make: Build finished! Hooray!"

re : clean all

obj/%.o : src/%.cpp
	echo "Make: Compiling $<"
	g++ -c $< -o $@

dirs:
	mkdir obj
	mkdir bin
	echo "Make: Created bin and obj directories"

clean:
	rm -f $(EXOBJECTS)
	echo "Make: removed $(EXOBJECTS)"
