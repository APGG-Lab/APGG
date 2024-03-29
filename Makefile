TARGET_EXEC ?= apgg_release

BUILD_DIR ?= ./build
SRC_DIRS ?= ./APGG

#CXX = g++-9 #If g++-9 is not your default, use this

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -Wall
LDFLAGS += -lstdc++ -lm -lstdc++fs -lpthread


.PHONY: clean

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

debug: CPPFLAGS += -DDEBUG -g
debug: all

release: CPPFLAGS += -O3
release: all


clean:
	$(RM) -r $(BUILD_DIR)/APGG

-include $(DEPS)

MKDIR_P ?= mkdir -p


