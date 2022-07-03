CC=gcc -m32 -Ilib -DSAMPGDK_AMALGAMATION -fno-stack-protector
CXX=g++ -m32 -Ilib -DSAMPGDK_AMALGAMATION -fno-stack-protector

OUTFILE=../Release/yt.so
OBJECTS=yt.o gdk/sampgdk.o sdk/amxplugin.o

CFLAGS=-c -m32 -O3 -fPIC -DLINUX -Isdk -Isdk/amx -Iinclude/ -include stddef.h -Wno-attributes -DHAVE_ALLOCA_H -DHAVE_STDINT_H
CXXFLAGS=$(CFLAGS)
LDFLAGS=-O3 -m32 -march=core2 -fexpensive-optimizations -fshort-wchar -shared

.PHONY: all clean

all: $(OUTFILE)

yt.o: yt.cpp gdk/sampgdk.h
	$(CXX) $(CFLAGS) $< -o $@

sampgdk.o: gdk/sampgdk.c gdk/sampgdk.h 
	$(CC) $(CFLAGS) $< -o $@

sdk/amxplugin.o: sdk/amxplugin.cpp sdk/plugin.h
	$(CXX) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $? -o $@

clean:
	rm -vf $(OBJECTS) $(OUTFILE)
