default: build
	${MAKE} check

e=20 17 14 11 03
e+=patterns
t=features.csv

build: $e $t

clean:
	rm -f $e $t || true
	rm -f *.gcov *.gcda *.gcno || true

CXXFLAGS+=-Wall -Wno-unused
CXXFLAGS+=-Wextra -Wno-missing-field-initializers
CXXFLAGS+=-Wpedantic
CXXFLAGS+=-Dgcc_extension
CXXFLAGS+=-include features.cpp
CXXFLAGS+=-g -fsanitize=leak
LDLIBS+=-pthread
CXXFLAGS+=--coverage

ifneq (, $(shell which g++-10))
20: CXX=g++-10
20: CXXFLAGS+=-fcoroutines -fconcepts -fgnu-tm
20: CXXFLAGS+=-fconcepts -fgnu-tm
else
20: CXX=clang++-10
20: CXXFLAGS+=-Wno-missing-braces -Wno-unused-parameter
endif

20: CXXFLAGS+=-std=c++2a

17 patterns: CXXFLAGS+=-std=c++17
14: CXXFLAGS+=-std=c++14
11: CXXFLAGS+=-std=c++11
03: CXXFLAGS+=-std=c++03

check: build
	for a in $e; do ./$$a || exit; done

features.csv:
	#./03 && ./11 && ./14 && ./17 && ./20
	bash -c "export features=1; join --nocheck-order <(join <(join <(join <(./03) <(./11)) <(./14)) <(./17)) <(./20)" \
		> $@

coverage: build
	${MAKE} check &> /dev/null
	for a in $e; do gcov ./$$a 2> /dev/null || exit; done
	grep -H '##' *cpp.gcov | sed 's/\.gcov: \+#\+: \+\([0-9]\+\):/:\1: untested:/'
