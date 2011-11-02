
OS := $(shell uname)
#ifeq ($(OS), Linux)
#endif

PROJECT := gtk
INSTALL_PATH = /usr/lib/neko

CFLAGS = -shared -g -O2 -Wall -DLINUX -DXP_UNIX=1 -DMOZ_X11 -D_DEBUG
NDLL = ndll/$(OS)/$(PROJECT).ndll
GTK_FLAGS := $(shell pkg-config --cflags --libs gtk+-2.0)
NEKO_FLAGS := -fPIC -shared -L/usr/lib/neko -lneko -lz -ldl
LDFLAGS = -Iinclude -I/usr/lib/neko/include
OBJ = src/hxgtk.o src/hxgtk_window.o

all : ndll

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(GTK_FLAGS) -c -o $@ $<
	
ndll : $(OBJ)
	$(CC) $(CFLAGS) -o $(NDLL) $(OBJ) $(LDFLAGS) $(GTK_FLAGS)

tests : tests/* Makefile
	cd tests && haxe build.hxml
	
tests-run : tests Makefile
	cd tests && neko $(PROJECT)_test.n

doc :
	cd doc && haxe build.hxml
	
install :
	cp $(NDLL) $(INSTALL_PATH)
	
clean:
	rm -f src/*.o
	rm -f $(NDLL)
	rm -f tests/*.n
	rm -f doc/*.xml doc/*.n doc/index.html
	rm -rf doc/content

.PHONY: all ndll tests tests-run clean
