TARGET = main
TEST = check
CC = g++
CFLAGS = -g -Wall -I/plog/ -I.
LIBS = -lpthread



GTEST = gtest-1.7.0/include
LIBGTEST = /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a
TESTDIR = tests


#-------

SRCS := main.cpp io_util.cpp moves.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

.PHONY: all clean

all: prog

run:
	./prog

prog: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -MMD -o $@ $<

clean:
	$(RM) prog $(OBJS) $(DEPS) $(TARGET) $(TEST)


-include $(DEPS)



# --------

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ) main.o
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -I $(GTEST) $(TESTDIR)/*.cc $(LIBGTEST) $(LIBS)
	./$(TEST)



install_gtest:
	cmake -S . -B build
	cmake --build build
	git submodule update

test:
	cmake -S . -B build
	cmake --build build
	cd build && ctest


format:
	find . -regex '.*\.\(cpp\|hpp\|cc\|c\|h\)' -exec clang-format -style=file -i {} \;


lint:
	cppclean src/