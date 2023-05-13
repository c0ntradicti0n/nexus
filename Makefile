#-------
TARGET = main
TEST = check
CC = g++
CFLAGS = -g -Wall -I/plog/ -I.
LIBS = -lpthread

SRCS := main.cpp io_util.cpp moves.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

BUILD_DIR := versions/$(shell git rev-parse --short HEAD)

.PHONY: all clean

all: prog

run:
	./$(BUILD_DIR)/prog

prog: $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -MMD -o $@ $<

clean:
	$(RM) $(BUILD_DIR)/prog $(OBJS) $(DEPS) $(TARGET) $(TEST)


-include $(DEPS)

# --------

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ) main.o
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

$(TEST): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) -I $(GTEST) $(TESTDIR)/*.cc $(LIBGTEST) $(LIBS)
	./$(BUILD_DIR)/$(TEST)


install_gtest:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	git submodule update

test:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	cd $(BUILD_DIR) && ctest --output-on-failure


format:
	find . -regex '.*\.\(cpp\|hpp\|cc\|c\|h\)' -exec clang-format -style=file -i {} \;


lint:
	cppclean src/

kill:
	killall -9 prog
