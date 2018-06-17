$(VERBOSE).SILENT:

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/
BINNAME = spectrum
GCCSUFFIX = -I/usr/include/SDL2 -DUSE_VCHIQ_ARM -I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads -D_REENTRANT -L/usr/lib/arm-linux-gnueabihf -lSDL2
COMPILER = g++

SRCFILES = $(wildcard $(SRCDIR)*.cpp)
OBJFILES = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCFILES))
BINFILE = $(BINDIR)$(BINNAME)
EXOBJECTS = $(wildcard $(OBJDIR)*.o)

help:
	echo "Makefile for Simple Spectrum Analyzer"
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
	$(COMPILER) -o $(BINFILE) $(OBJFILES) $(GCCSUFFIX)
	echo "Make: Build finished! Hooray!"

re : clean all

obj/%.o : src/%.cpp
	echo "Make: Compiling $<"
	$(COMPILER) -c $< -o $@ $(GCCSUFFIX)

dirs:
	mkdir obj
	mkdir bin
	echo "Make: Created bin and obj directories"

clean:
	rm -f $(EXOBJECTS)
	echo "Make: removed $(EXOBJECTS)"
