SHELL=/bin/sh

.PHONY: clean

TARGET=challenge3
CRYPTOPALS=../../libcryptopals

CXXFLAGS=-g -std=c++0x
INCLUDES=-I$(CRYPTOPALS)/include

SOURCES=main.cpp
OBJECTS=$(SOURCES:%.cpp=%.cpp.o)

default: $(TARGET)

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) -o $(@) $(<)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(@) $(^) -L$(CRYPTOPALS) -lcryptopals -Wl,-rpath=$(CRYPTOPALS)

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
