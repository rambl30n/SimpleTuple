SOURCES := Tuple_ut.cpp

# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)
CC := g++-8
CFLAGS := -ggdb3 -std=c++17
LIBDIRS := \
	-L $(GTEST_LIB)

LFLAGS :=

LIBS := -lgtest -lgtest_main

INCLUDES := \
	-I $(GTEST_INC)

all: unit_test run

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
unit_test: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBDIRS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	find . -name *.o -delete
	find . -name unit_tests -delete

run : unit_test
	./unit_test
