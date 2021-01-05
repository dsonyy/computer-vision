# cpp compiler
CXX=cl
# compiler flags
CXXFLAGS=-std:c++17 -O2 -Fe./build/$(F).exe -Fo./build/$(F).o
# used libraries
LIBS=
# compiler library flags
LFLAGS=-link
# files to compile (without an extension)
F=test

.PHONY: build

release: build
debug: 

build:
	$(CXX) $(F).cpp $(CXXFLAGS) $(LFLAGS) $(LIBS)

clean:
	powershell -noprofile rm build/*
