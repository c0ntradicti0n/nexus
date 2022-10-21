TARGET = network
TEST = check
CC = clang
CFLAGS = -g -Wall
LIBS = -lpthread

DEPS = basis.h
OBJ = bp.o main.o

GTEST = gtest-1.7.0/include
LIBGTEST = /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a
TESTDIR = tests

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ) main.o
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -I $(GTEST) $(TESTDIR)/*.cc $(LIBGTEST) $(LIBS)
	./$(TEST)

clean:
	rm -rf *.o *.gch
	rm -f $(TARGET) $(TEST)

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