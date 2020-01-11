all: 20 17 14 11 03
CXXFLAGS+=-Wall -Wextra -Wno-long-long -Wno-unused

ifneq (, $(shell which g++-9))
CXX=g++-9
20: CXXFLAGS+=-fconcepts -fgnu-tm
else
20: CXX=clang++
endif

20: CXXFLAGS+=-std=c++2a

17: CXXFLAGS+=-std=c++17
14: CXXFLAGS+=-std=c++14
11: CXXFLAGS+=-std=c++11
03: CXXFLAGS+=-std=c++03
