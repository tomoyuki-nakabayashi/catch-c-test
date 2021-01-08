CFLAGS := -Wall -Wextra -std=c11
CXXFLAGS := -Wall -Wextra -std=c++11

BUILD_DIR := build
BIN := $(BUILD_DIR)/test

ROOT_REL := ../
ROOT := $(abspath $(ROOT_REL))

CATCH_DIR := ./catch
CATCH_HEADER := catch.hpp

INCLUDE_DIRS := \
	-I$(ROOT)/include \
	-I$(CATCH_DIR)

SRC_DIR := $(ROOT)/src
SRCS := \
	$(SRC_DIR)/hoge.c
TEST_SRCS := \
	test_hoge.cpp

OBJ_FILES = $(SRCS:%.c=$(BUILD_DIR)/%.o) $(TEST_SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEP_FILE = $(OBJ_FILES:%.o=%.d)

## creates build directory & downloads catch.hpp
prepare: $(BUILD_DIR) $(CATCH_DIR)/$(CATCH_HEADER)

## build test binary
test: prepare $(BIN)

## run test binary
run: test
	./$(BIN)

## remove build directory
clean:
	rm -rf build

## remove all files it makes your next build much slower
cleanall:
	rm -rf build
	rm -rf $(CATCH_DIR)

.PHONY: run clean cleanall

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CATCH_DIR)/$(CATCH_HEADER):
	mkdir -p catch
	curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.1/catch.hpp -o $@

## catch.hpp のビルドに時間がかかるので、main.cpp とだけビルドしてキャッシュ
$(BUILD_DIR)/main.o: main.cpp $(CATCH_DIR)/$(CATCH_HEADER)
	mkdir -p $(BUILD_DIR)
	$(CXX) main.cpp -c -o $@ ${INCLUDE_DIRS} $(CXXFLAGS)

-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) ${INCLUDE_DIRS} -MMD  -c $< -o $@

${BUILD_DIR}/%.o : %.cpp
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) ${INCLUDE_DIRS} -MMD  -c $< -o $@

$(BIN): $(BUILD_DIR)/main.o ${OBJ_FILES}
	$(CXX) $^ $(CXXFLAGS) ${INCLUDE_DIRS} -o $@
