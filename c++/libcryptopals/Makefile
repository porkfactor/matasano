SHELL=/bin/sh

.PHONY: clean

TARGET_SHARED=libcryptopals.so
MAJOR=1
MINOR=0
REVISION=0

CXXFLAGS=-g -std=c++0x
INCLUDES=-I$(PWD)/include

SOURCES=encoding.cpp
OBJECTS=$(SOURCES:%.cpp=%.cpp.o)

default: $(TARGET_SHARED)

%.cpp.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -fPIC -o $(@) $(<)

$(TARGET_SHARED).$(MAJOR).$(MINOR).$(REVISION): $(OBJECTS)
	$(CXX) -o $(@) -shared -Wl,-Bdynamic $(^) -Wl,-soname=$(TARGET_SHARED).$(MAJOR)

$(TARGET_SHARED).$(MAJOR): $(TARGET_SHARED).$(MAJOR).$(MINOR).$(REVISION)
	ln -sf $(<) $(@)

$(TARGET_SHARED): $(TARGET_SHARED).$(MAJOR)
	ln -sf $(<) $(@)

clean:
	rm -f $(TARGET_SHARED) $(TARGET_SHARED).$(MAJOR) $(TARGET_SHARED).$(MAJOR).$(MINOR).$(REVISION)
	rm -f $(OBJECTS)
