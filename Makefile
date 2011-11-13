
OS := $(shell uname)
PROJECT := gtk
NDLL := ndll/$(OS)/$(PROJECT).ndll
INSTALL_PATH := /usr/lib/neko
OBJS = src/hxgtk.o src/hxgtk_window.o

all: $(NDLL)

%.o: %.c
	$(CC) -O3 -Wall -Iinclude -I/usr/lib/neko/include $(shell pkg-config --cflags gtk+-2.0) -c -o $@ $<

$(NDLL): $(OBJS) src/*.c
	$(CC) -shared -Iinclud -I/usr/lib/neko/include $(OBJS) $(shell pkg-config --libs gtk+-2.0) -o $(NDLL)
	
build: $(NDLL)

install: build
	cp $(NDLL) $(INSTALL_PATH)
	
tests : build
	(cd tests; haxe build.hxml)
	
tests-run : tests Makefile
	(cd tests; neko test.n)

doc:
	(cd doc; haxe build.hxml)
	
clean:
	rm -f src/*.o $(NDLL)
	rm -f tests/*.n
	rm -f doc/*.xml doc/*.n doc/index.html && rm -rf doc/content
	
.PHONY: all build install tests tests-run doc clean
