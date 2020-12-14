CXX      := -c++
CXXFLAGS := -g -std=c++17 -pedantic-errors -Wall -Wextra
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := orderBook
INCLUDE  := -ISource/
SRC      :=                      		\
	$(wildcard *.cpp)					\
	$(wildcard Source/Storage/*.cpp) 	\
	$(wildcard Source/View/*.cpp) 		\
	$(wildcard Source/Commands/*.cpp)	\
	$(wildcard Source/Parser/*.cpp)		\

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
		:= $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
