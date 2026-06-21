CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include

ifeq ($(OS), Windows_NT)
    LIB_EXT = dll
    LDFLAGS = 
else
    LIB_EXT = so
    LDFLAGS = -ldl
endif

all: build_dir \
     build/libCaesar.$(LIB_EXT) \
     build/libAtbash.$(LIB_EXT) \
     build/libTrithemius.$(LIB_EXT) \
     build/main

build_dir:
	mkdir -p build

build/libCaesar.$(LIB_EXT): crypto/Caesar.cpp
	$(CXX) -fPIC -shared $^ -o $@

build/libAtbash.$(LIB_EXT): crypto/Atbash.cpp
	$(CXX) -fPIC -shared $^ -o $@

build/libTrithemius.$(LIB_EXT): crypto/Trithemius.cpp
	$(CXX) -fPIC -shared $^ -o $@

build/main: src/main.cpp \
            src/menuCaesar.cpp \
            src/menuAtbash.cpp \
            src/menuTrithemius.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf build

.PHONY: all build_dir clean