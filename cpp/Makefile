all: 20 17 14 11 03
CXXFLAGS+=-Wall -Wno-unused
CXXFLAGS+=-Wextra -Wno-missing-field-initializers
CXXFLAGS+=-Wpedantic
CXXFLAGS+=-Dgcc_extension
CXXFLAGS+=-include features.cpp

ifneq (, $(shell which g++-9))
CXX=g++-9
20: CXXFLAGS+=-fconcepts -fgnu-tm
else
20: CXX=clang++
20: CXXFLAGS+=-Wno-missing-braces
endif

20: CXXFLAGS+=-std=c++2a

17: CXXFLAGS+=-std=c++17
14: CXXFLAGS+=-std=c++14
11: CXXFLAGS+=-std=c++11
03: CXXFLAGS+=-std=c++03
